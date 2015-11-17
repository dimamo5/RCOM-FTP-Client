#ifndef _UTILS_H
#define _UTILS_H

#define USAGE "usage: download ftp://[<user>:<password>@]<host>/<url-path>\n"
#define valid_regEx "ftp://[[A-Za-z0-9]+:[A-Za-z0-9]+@][A-Za-z0-9._~:?#@!$&'()*+,:;=-]+/[A-Za-z0-9._~:?#@!$&'()*+,:;=-]+"

#define MAX_BUFFER_SIZE 100
#define SERVER_PORT 21
#define QUIT_CMD "quit\n"

typedef struct clientTCP_t {

	int cmd_socket_fd;
	int dw_socket_fd;

	/*info from argv[1]*/
	char username[MAX_BUFFER_SIZE];
	char password[MAX_BUFFER_SIZE];
	char host_address[MAX_BUFFER_SIZE];
	char sv_file_path[MAX_BUFFER_SIZE];

} clientTCP;

#endif