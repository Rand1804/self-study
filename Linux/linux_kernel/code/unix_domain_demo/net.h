#ifndef __MAKEU_NET_H__
#define __MAKEU_NET_H__

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <errno.h>
#include <arpa/inet.h>
#include <pthread.h>


#define BACKLOG 5
#define QUIT_STR "quit"
#define UNIX_DOMAIN_FILE "/tmp/my_domain_file.1"

#endif