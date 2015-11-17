#ifndef _CLIENTTCP_H
#define _CLIENTTCP_H

#include "utils.h"

int create_connection_socket(char* string);
int write_cmd(int fd, char* cmd);
int login_communication(char* ip);
int enable_passive_mode(clientTCP * client);
int download_communication(clientTCP * client);
int quit(clientTCP * client);

#endif