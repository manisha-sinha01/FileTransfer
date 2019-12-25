#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>

#define FILENAMELEN 256
#define BUFSIZE 10000

int sendFile(int socket, const char* path , int key){

    char filename[FILENAMELEN];
    char buf[BUFSIZE];
    FILE* f;
    int sum=0, result_read,filesize;

    srand(key);

    if((f = fopen(path, "rb"))== NULL)
        printf("Error in send\n");
    
    if(strrchr(path, '/'))
        sprintf(filename, "%s", strrchr(path,'/')+1);
    else
    {
            sprintf(filename, "%s",path);
    }

    fseek(f,0,SEEK_END);
    filesize = ftell(f)/1024;
    fseek(f,0,SEEK_SET);

    if(send(socket, filename, FILENAMELEN,0) == -1)
        printf("Error\n");
    send(socket, &filesize,4,0);

    while((result_read == fread(buf,1,BUFSIZE,f))){
        int i,n,k;
        for(i=0;result_read!=i;i++)
            buf[i] = buf[i] ^ rand();
        
        sum+= write_socket(socket, buf, result_read);

    }  

    if(filesize == sum/1024)
        printf("File sent");
    else
    {
        printf("error to be handled\n");
    }
    fclose(f);
    return 0;
      

}


int write_socket(int socket, void* buf, int n){

    int result;
    int index =0,left =n;

    while(left > 0){
        result= send(socket, (char*)buf, n, 0);

        if(result == 0)
            return index;

        if(result == -1)
            return -1;
        
        index += result;
        left -= result;

    }
        return index;
}