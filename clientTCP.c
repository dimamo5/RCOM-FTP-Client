#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
/* libs */
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <netdb.h>
#include <string.h>

/* header files */
#include "parser.h"
#include "getip.h"
#include "download.h"
#include "clientTCP.h"


/* CREATES A SOCKET FOR COMMUNICATION | RETURNS SOCKET FILE DESCRIPTOR */
int create_connection_socket(char * ip, int port){

	int	sockfd;
	struct	sockaddr_in server_addr;

	/*server address handling*/
	bzero((char*)&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(ip);	/*32 bit Internet address network byte ordered*/
	server_addr.sin_port = htons(port);		/*server TCP port must be network byte ordered */
    
	/* open an TCP socket */
	if ((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
		perror("create_connection_socket:socket()");
    	exit(1);
	}

	/* connect to the server */
	if(connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){    	
    	perror("create_connection_socket:connect()");
		exit(1);
	}
	
	return sockfd;
}

/* writes cmd to fd */
int write_cmd(int fd, char* cmd){  	 

	return write(fd, cmd, strlen(cmd));
}

int read_reply(int sock_fd){

	int reply_code;
	char reply[MAX_BUFFER_SIZE], ignore[MAX_BUFFER_SIZE];

	if(read(sock_fd, reply, MAX_BUFFER_SIZE) <= 0){
		fprintf(stderr, "ClientTCP:read_reply() - Error reading reply\n");
		exit(1);
	}

	sscanf(reply, "%d %s", &reply_code, ignore);
	printf("%s\n",reply);
	return reply_code;
}


int login_communication(char* ip, clientTCP* client){

	int reply;
	char cmd[MAX_BUFFER_SIZE];

	/*  connects to server, read reply fom sv and ignores it  */
	client->cmd_socket_fd = create_connection_socket(ip, SERVER_PORT);
	read_reply(client->cmd_socket_fd);

	/* send username, read reply from sv and ignores it*/
	sprintf(cmd, "%s %s\n", USER, client->username);
	write_cmd(client->cmd_socket_fd, cmd);
	read_reply(client->cmd_socket_fd);


	/* send password, read reply and interprets it */
	sprintf(cmd, "%s %s\n", PW, client->password);
	write_cmd(client->cmd_socket_fd, cmd);
	reply = read_reply(client->cmd_socket_fd);

	if(reply != USER_LOGGED){
		fprintf(stderr, "Log in denied. Verify your credentials. Exiting now.\n\n");
		exit(1);
	}

	return 0;
}


int enable_passive_mode(clientTCP * client){

	char cmd[MAX_BUFFER_SIZE], reply[MAX_BUFFER_SIZE], ignore[MAX_BUFFER_SIZE], ip_str[MAX_BUFFER_SIZE];
	int code, ip[4], port[2];

	/* set passive mode with cmd "pasv" */
	sprintf(cmd, "%s\n", PASV);
	write_cmd(client->cmd_socket_fd, cmd);
	
	if(read(client->cmd_socket_fd, reply, MAX_BUFFER_SIZE) <= 0){
		fprintf(stderr, "Passive mode: problem reading reply from sv\n");
		exit(1);
	}

	//reply format ex: 227 Entering Passive Mode (193,136,28,12,19,91)
	sscanf(reply, "%d %s %s %s (%d,%d,%d,%d,%d,%d)",&code,ignore,ignore,ignore,
	 												&ip[0],&ip[1],&ip[2],&ip[3],
	 											    &port[0],&port[1]);
	
	sprintf(ip_str, "%d.%d.%d.%d", ip[0],ip[1],ip[2],ip[3]);
	
	/* update atributos do cliente */
	strcpy(client->dw_ip, ip_str);
	client->dw_port = 256*port[0]+port[1];

	printf("%s\n%s %d\n",reply,client->dw_ip,client->dw_port);

	return 0;
}


int download_communication(clientTCP * client){

	char cmd[MAX_BUFFER_SIZE];
	int code;

	/*   cmd retrieve file   */
	sprintf(cmd, "%s %s\n", RETR, client->sv_file_path);
	
	printf("%s\n",cmd);

	write_cmd(client->cmd_socket_fd, cmd);
	code = read_reply(client->cmd_socket_fd);

	if(code != RETR_SUCCESS){
		fprintf(stderr, "Error retrieving file. Try checking the file path.\n" );
		exit(1);
	}

	/* estabelece conexao via scoket com porto de download */
	client->dw_socket_fd = create_connection_socket(client->dw_ip, client->dw_port);
	read_reply(client->dw_socket_fd); //le resposta do connect e ignora

	return 0;
}


int quit(clientTCP * client){

	write(client->cmd_socket_fd, QUIT, sizeof(QUIT));
	//TODO verificar retorno do write

	//TODO resposta do quit
	char quit_answer[MAX_BUFFER_SIZE];
	read(client->cmd_socket_fd, quit_answer, MAX_BUFFER_SIZE);

	//TODO se quit_answer estiver fixe close sockets

	close(client->cmd_socket_fd);
	//close(client->dw_socket_fd);

	return 0;
}