/*
Name: Xiaoyan Xu
Student  Number: 11229743
NSID: xix799
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define  MAXDATASIZE 300
#define INPUTSIZE 20

void getInput(char *buffer){
    char input[INPUTSIZE];
    printf("Enter the day: ");
    fgets(input, sizeof(input), stdin);
    strcpy(buffer,input);
    buffer[strcspn(buffer,"\n")]='\0';

}


 
int main(int argc, char *argv[]){
    int  socketfd, num, len, PORT, WinSize, timeoutVal;
    char  buf[MAXDATASIZE];
    char buffer[INPUTSIZE];
    struct hostent *host;
    struct sockaddr_in server;
    char msg[INPUTSIZE];
    socklen_t addrlen;
    addrlen = sizeof(server);
    flag = 0;

    // arguments: IP address of the receiver, port number, maximum sending window size,  timeout value 
    if(argc!=5){
        printf("Usage: ./clienttcp hostname, port number, maximum sending window size, timeout value \n");
        exit(1);
    }
    
    if((host=gethostbyname(argv[1]))==NULL){
        printf("gethostbyname()error\n");
        exit(1);
    }

    if((PORT=atoi(argv[2]))==0){
        printf("get port error\n");
        exit(1);
    }

    if((WinSize=atoi(argv[3]))==0){
        printf("get port error\n");
        exit(1);
    }
    
    if((timeoutVal=atoi(argv[4]))==0){
        printf("get port error\n");
        exit(1);
    }

    memset(&server, 0, sizeof(server));
    server.sin_family= AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr =*((struct in_addr *)host->h_addr);

    if((socketfd=socket(AF_INET, SOCK_DGRAM, 0))==-1){
        printf("socket()error\n");
        exit(1);
    }

    while(1){
        memset(buffer,0,INPUTSIZE);
        memset(buf,0,MAXDATASIZE);
        getInput(buffer);
        switch (validateInput(buffer)){
            case -1:
            printf("invalid day\n");
            break;
            case 0:
            flag = 1;
            break;
            default:
            strcpy(msg,buffer);

            len = strlen(msg);
            sendto(socketfd, msg, len, 0, (struct sockaddr*)&server, sizeof(server));
            if((num=recvfrom(socketfd,buf,MAXDATASIZE,0, (struct sockaddr*)&server, &addrlen)) == -1){
                printf("recv() error\n");
                exit(1);
            }
            buf[num]='\0';
            printf("%s",buf);                 
        }
        if(flag==1){break;}
    }
    close(socketfd); 
    return 0;
}
