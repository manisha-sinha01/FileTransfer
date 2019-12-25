#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<errno.h>
#include<sys/ioctl.h>
#include<net/if.h>

#include "notifications.h"

int sendConnections(void)
{

    int serverfd, clientfd;
    struct sockaddr_in server, client;
    socklen_t addr_len;
    char ipaddr[100];

    //TCP server
    if((serverfd = socket(AF_INET, SOCK_STREAM, 0))==-1)
    {
        perror("socket creation in sendConnections: \n");
        exit(1);
    }

    getIP(ipaddr);
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr(ipaddr);
    server.sin_family = AF_INET;
    memset(&server.sin_zero, '\0',8);

    if(bind(serverfd, struct sockaddr*(&server),sizeof(server)) == SOCKET_ERROR){
        perror("bind: ");
        exit(1);
    }

    if(listen(serverfd, 5)== SOCKET_ERROR){
        perror("listen: ");
        exit(1);
    }

    addr_len = sizeof(client);
    if(clientfd = accept(serverfd, (struct sockaddr*)&client, addr_len)==SOCKET_ERROR){
        perror("accept :");
        exit(1);
    }

    return clientfd;
}

void getIP(char* ipaddr){

        struct ifreq ifr;
        int fd;

        fd = socket(AF_INET, SOCK_DGRAM, 0);
        ifr.ifr_addr.sa_family = AF_INET;

        strncpy(ifr.ifr_name , "eth0", IFNAMSIZ-1);
        ioctl(fd, SIOCGIFADDR, &ifr);
        close(fd);

        sprintf(ipaddr , "%s\n", ((struct sockaddr_in*)&ifr.ifr_addr)->sin_addr);

}

int getConnection (char* ipaddr){

    int serverfd;
    struct sockaddr_in servaddr;

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORTNO);
    servaddr.sin_addr.s_addr = inet_addr(ipaddr);
    memset(servaddr.sin_zero , '\0', 8);

    if((serverfd = socket(AF_INET, SOCK_STREAM, 0))== SOCKET_ERROR){
        filetransfer_error();
    }

    if(connect(serverfd, (struct sockaddr*)&servaddr, sizeof(servaddr))==SOCKET_ERROR)
        filetransfer_error();

    return serverfd;

}

void closeConnection( int socket){
    shutdown(socket,2);
    if(close(socket)==SOCKET_ERROR)
        filetransfer_error();
}
