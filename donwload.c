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
	
	int ret = 0;
	char buffer[BUFFER_MAX_SIZE];

	//TODO IMPLEMENTAR ALARME PARA O CASO DE HAVER DESCONEXAO 
	//VISTO QUE READ FICA BLOQUEADO

	while( (ret = read(dw_socket_fd, array, BUFFER_MAX_SIZE) > 0 ){

		/* escreve packet lido no ficheiro */
		write(fd, array, ret);
	}

	if(ret < 0 ){
		fprintf(stderr, "download: Error reading ");
		exit(0);
	}

	return 0;
}


