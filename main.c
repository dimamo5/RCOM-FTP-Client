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
#include <fcntl.h>

#include "clientTCP.h"
#include "parser.h"
#include "getip.h"
#include "utils.h"
#include "download.h"


//TODO MENU COM TAMANHO DO BUFFER (NAO PODE SER SUPERIOR A 8000) (8kBs)
//COM USER A DECIDIR FILE NAME DO FICHEIRO GUARDADO DEPOIS DE DW
//ETC

int main(int argc, char** argv){

	if(argc != 2){
		printf("%s", USAGE);
		return -1;
	}

	int	ret, fd;
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

	printf("hostadress: %s\nip: %s\n",client.host_address,conx_ip);

   	/* callback to login function to server */
	login_communication(conx_ip, &client);


	/* Enter passive mode */
	enable_passive_mode(&client);	

	/* callback to connetion download */
	if(download_communication(&client)){
		return quit(&client);
	}

	/* creates file vesile to download data */
	fd = open(client.file_name, O_CREAT|O_WRONLY, 0666);

	/* callback to download that creates a file, reads from server and writes to file*/
	download(client.dw_socket_fd, fd);
	printf("Succesfully received file.\n");

	/* callback to quit function */	
	return quit(&client);

	//TODO: DESCOMENTAR LINHA DA FUNCAO QUIT (close(..))
}


