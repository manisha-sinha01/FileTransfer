#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#define SOCKET_ERROR -1

#define FILENAMELEN 256
#define FILEPATHLEN 256
#define BUFFERSIZE 10000

void getFile(int socket , const char* path, int key){

    FILE* f;
    char filename[FILENAMELEN];
    char filepath[FILEPATHLEN];
    char buf[BUFFERSIZE];
    int filesize, read_result,f,sum =0, filesize_check;

    srand(key);

    if(recv(socket,filename, FILENAMELEN,0) == SOCKET_ERROR)
        printf("There is receive error\n");
    recv(socket, &filesize, sizeof(int) ,0);

    if(path == NULL){
        sprintf(filepath , "%s" , filename);
    }else{
        sprintf(filepath, "%s/%s", path, filename);
    }

    if((f=fopen(filepath,"wb")) == NULL)
        printf("File acess error\n");
    
    while((read_result = read_socket(socket, buf, BUFFERSIZE)) != -1 ){
        int i, n, k;
        if(read_result == 0)
            break;

        for(i=0;i<read_result;i++)
            buf[i] = buf[i] ^ rand();

        sum += fwrite(buf,1 , read_result,f);

        if(filesize >= 1){
            k = n = (sum/1024 * 100)/(filesize);
            n /= 2;
            while(n--)
                printf("=");
            printf(">(%%%d)\r",k);
        }

    }

        if(read_result == -1)
            printf("File download failed\n");

        fseek(f,0,SEEK_END);
        filesize_check = ftell(f)/1024;

        if(filesize_check == filesize)
            printf("File downloaded\n");
        else
        {
            printf("File transfer unsuccessful\n");
        }

    fclose(f);
    return 0;

}

static int read_socket(int socket , void* buf, int size){

    int result;
    int index = 0;
    int left = size;

    while(left > 0){
        result = recv(socket, (char*)buf+index, left, 0);

        if(result == 0)
        return index;

        if(result == -1)
            return -1;

        index += result;
        left -= result; 
    }

    return index;
}