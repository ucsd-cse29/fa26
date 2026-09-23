#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <assert.h>

void start_server(void(*handler)(char*, int), int port);

#define BUFFER_SIZE 2048

#endif
