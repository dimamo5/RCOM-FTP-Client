#include <sys/types.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parser.h"

int url_input_validator(char* url){

	int reti;
	char msgbuf[100];
	regex_t regex;

	/* Compile regular expression */

	reti = regcomp(&regex, valid_regEx, REG_EXTENDED);
    if( reti ){ fprintf(stderr, "Could not compile regex\n"); return -1; }


    /* Execute regular expression */
    reti = regexec(&regex, url, 0, NULL, 0);
    if( !reti ){
            return 0;
    }
    else if( reti == REG_NOMATCH ){
        return -1;
    }
    else{
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }
}

void get_info_from_string(char* argv, clientTCP * client){

	 char * usr_begin, *pw_begin, *host_begin, *path_begin;
	 int num_bytes;

	 usr_begin = strchr(argv,'['); 	
	 pw_begin = strchr(argv+=4,':'); //ignora primeiro ":"
	 host_begin = strchr(argv,']');	
	 path_begin = strchr(argv+=6,'/'); //ignora primeiros //

	 //parse username
	 num_bytes = (pw_begin - usr_begin ) - 1;	
	 parse_information(client->username, usr_begin + 1, num_bytes);
	 
	 //parse pw
	 num_bytes = (host_begin-1 - pw_begin) - 1;  // 1º -1 é relativo ao shift para posicao do @ 
	 parse_information(client->password, pw_begin + 1, num_bytes);

	 //parse hostname
	 num_bytes = (path_begin - host_begin) - 1;
	 parse_information(client->host_address, host_begin + 1, num_bytes);

	 //parse filename_path
	 strcpy(client->sv_file_path, path_begin+1);  //ja adiciona nulo terminador

	 printf("usr:%s\npw:%s\nhost:%s\npath:%s\n",client->username,client->password, client->host_address,client->sv_file_path );
}

void parse_information(char* var_to_be_set, char* begin, int size){

	if(size > MAX_BUFFER_SIZE){
		fprintf(stderr, "PARSER-parse_information(): Buffer size exceeded\n");
		exit(1);
	}

	memcpy(var_to_be_set, begin, size);

	var_to_be_set[size] = 0; //nulo terminador
}
