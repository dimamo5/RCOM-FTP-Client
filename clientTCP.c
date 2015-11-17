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
#include <strings.h>

/* header files */
#include "parser.h"
#include "getip.h"
#include "download.h"
#include "clientTCP.h"


/* CREATES A SOCKET FOR COMMUNICATION | RETURNS SOCKET FILE DESCRIPTOR */
int create_connection_socket(char * ip, int port){

	int	sockfd, ret;
	struct	sockaddr_in server_addr;

	/*server address handling*/
	bzero((char*)&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(ip);	/*32 bit Internet address network byte ordered*/
	server_addr.sin_port = htons(port);		/*server TCP port must be network byte ordered */
    
	/* open an TCP socket */
	if ((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
		perror("create_connection_socket:socket()");
    	exit(0);
	}

	/* connect to the server */
	if(connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){    	
    	perror("create_connection_socket:connect()");
		exit(0);
	}
	
	return sockfd;
}

/* writes cmd to fd */
int write_cmd(fd, char* cmd){   	
   	int bytes;   	

	bytes = write(sockfd, buf, strlen(buf));

	printf("Bytes escritos %d\n", bytes);
	return bytes;
}



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>ENVIAR COMANDOS SEMPRE COM \n no final



int login_communication(char*  ip){

	create_connection_socket(ip, SERVER_PORT);

	//fazer parsing das respostas
	//ler resposta do connect realizado na func acima

	//ENVIAR LOGIN CREDENTIALS ...

	return 0;
}


int enable_passive_mode(clientTCP * client){

	//write pasv

	//ler resposta : ip e fazer respectivo parsing
	//parse_pasv_reply(char * reply, client);

}


int download_communication(clientTCP * client){

	//TODO ENVIAR retr 
	// sprintf com \n no final

	//write(client->cmd_socket_fd, )


	create_connection_socket();
	//TODO nao ler resposta do connect realizado na func acima

	return 0;
}


int quit(clientTCP * client){

	write(client->cmd_socket_fd, QUIT_CMD, sizeof(QUIT_CMD));
	//TODO verificar retorno do write

	//TODO resposta do quit
	char quit_answer[MSG_MAX_SIZE];

	read(client->cmd_socket_fd, quit_answer, MSG_MAX_SIZE);

	//TODO se quit_answer estiver fixe close sockets

	close(client->cmd_socket_fd);
	close(client->dw_socket_fd);

	return 0;
}