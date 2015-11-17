#ifndef _PARSER_H
#define _PARSER_H

#include "utils.h"

int url_input_validator(char* url);
void get_info_from_string(char* argv, clientTCP * client);
void parse_information(char* var_to_be_set, char* begin, int size);

#endif