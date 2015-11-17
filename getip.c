#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <netdb.h> 
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#include "getip.h"

void getIP(char* address, char* ip)
{
    struct hostent * h;

    if ((h = gethostbyname(address)) == NULL) {  
        herror("gethostbyname");
        exit(1);
    }

    strcpy(ip, inet_ntoa(*((struct in_addr *)h->h_addr)));  
}
