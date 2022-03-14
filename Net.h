#ifndef _NET_H_
#define _NET_H_

#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#include<errno.h>  
#include<sys/types.h>  
#include<sys/socket.h>  
#include<netinet/in.h>  
#include<unistd.h>
#include<sys/wait.h>

#define DEFAULT_PORT 8000  
#define MAXLINE 1024



int Net_init();
int Net_listen();
int Net_accept();
char* Net_recv(int* num);
int Net_connect_close();
int Net_socket_close();
#endif
