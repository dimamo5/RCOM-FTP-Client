#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <netdb.h>
#include <strings.h>

#include "clientTCP.h"
#include "parser.h"
#include "getip.h"
#include "utils.h"

int main(int argc, char** argv){

	if(argc != 2){
		printf("%s", USAGE);
		return -1;
	}

	int	ret;
	char conx_ip[MAX_BUFFER_SIZE];
	clientTCP client;

	puts(argv[1]);

	//parsing argv[1] -> URL
	ret = url_input_validator(argv[1]);
	if(ret != 0){	printf("Invalid input: %s",USAGE);	return -1; }
	printf("URL match success\n");

	//converter string em elementos (username/pw/host_Addres/file_to_download_path)
	get_info_from_string(argv[1], &client);
	printf("information parsed\n");

	//converter address em ip
	getIP(client.host_address,conx_ip);
	printf("Got ip\n");

	//printf("hostadress: %s\nip: %s\n",client.host_address,conx_ip);
	return 0;

   	/* callback to login function to server */
	login_communication(conx_ip);


	/* callback TO  CONNECTION DOWNLOAD/IP */
	//ret = download_communication(dw_ip);

	/* callback to download function dat returns when finished downloading file*/
	/*int dw_file_fd = open("testfile.txt", O_WRONLY);
	download(dw_socket_fd, dw_file_fd);*/


	/* callback to quit function */
	return quit(&client);
}


