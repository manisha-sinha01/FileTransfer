#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<errno.h>

int sendConnections(){

    int serverfd, clientfd;
    struct sockaddr_in server, client;

    if((serverfd = socket(AF_INET, SOCK_STREAM, 0))==-1)
    {
        perror("socket creation in sendConnections: \n");
        exit(1);
    }

    

}