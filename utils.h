#ifndef _UTILS_H
#define _UTILS_H

#define USAGE "usage: download ftp://[<user>:<password>@]<host>/<url-path>\n"
#define valid_regEx "ftp://[[A-Za-z0-9]+:[A-Za-z0-9]+@][A-Za-z0-9._~:?#@!$&'()*+,:;=-]+/[A-Za-z0-9._~:?#@!$&'()*+,:;=-]+"

#define MAX_BUFFER_SIZE 256
#define SERVER_PORT 21

#define USER "user"
#define PW "pass"
#define PASV "pasv"
#define RETR "retr"
#define QUIT "quit\n"

#define USER_LOGGED 230
#define RETR_SUCCESS 150

typedef struct clientTCP_t {

	/*info from argv[1]*/
	char username[MAX_BUFFER_SIZE];
	char password[MAX_BUFFER_SIZE];
	char host_address[MAX_BUFFER_SIZE];
	char sv_file_path[MAX_BUFFER_SIZE];

	int cmd_socket_fd;
	int dw_socket_fd;
	
	char dw_ip[MAX_BUFFER_SIZE];
	int dw_port;

} clientTCP;

#endif