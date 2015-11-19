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

#define BUFFER_MAX_SIZE 8000  /*  defines a connection of ~~8KB/s  */

int download(int dw_socket_fd, int dw_file_fd){
	
	int ret;
	char buffer[BUFFER_MAX_SIZE];

	//TODO IMPLEMENTAR ALARME PARA O CASO DE HAVER DESCONEXAO 
	//VISTO QUE READ FICA BLOQUEADO

	while( (ret = read(dw_socket_fd, buffer, BUFFER_MAX_SIZE)) > 0 ){

		/* escreve packet lido no ficheiro */
		write(dw_file_fd, buffer, ret);
	}

	if(ret < 0 ){
		fprintf(stderr, "download: Error reading ");
		exit(0);
	}

	close(dw_file_fd);

	return 0;
}


