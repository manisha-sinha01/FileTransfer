#include<stdio.h>
#include<stdlib.h>
#include "connections.h"

int main(int argc, char* argv[]){

    int socket;
    char c;
    int key, sendFlag=0, getFlag=0;
    char* ipaddr;
    char *filepath = NULL;

    if(argc<2){
        helpFunc();
    }

    while((c == getopt(argc,argv ,"hg:p:l:s"))!=-1){
        switch(c){
            case h:
                helpFunc();
                break;
            case s:
                sendFlag=1;
                //sendFunc(sendFlag);
                break;
            case g:
                getFlag=1;
                //getFunc(getFlag);
                ipaddr = optarg;
                break;
            case p:
                key = atoi(optarg);
                break;
            case l:
                filepath = optarg;
                break;
            case h:
            default:
                helpFunc();
                break;
        }
    }

    if(sendFlag){
        socket = sendConnection();
        sendFile(socket, filepath, key);
        closeConnection(socket);
    }       

    if(getFlag){
        socket = getConnection(ipaddr);
        getFile(socket, filepath, key);
        closeConnection(socket);
    } 

    return 0;
}

void helpFunc(){

        printf("Please find below commands for using File-Transfer \n \
                1. Send a file :file-transfer -s -p <password> -l <filepath> \n \
                2. Get file with path :file-transfer -g <ipaddr> -p <password> -l <folderpath> \n \
                3. Get file without path : file-transfer -g <ipaddr> -p <password>\n \
                4. For help : file-transfer h\n");

        exit(1);

}