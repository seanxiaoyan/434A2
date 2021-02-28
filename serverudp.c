/*
Name: Xiaoyan Xu
Student  Number: 11229743
NSID: xix799
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
     
#define  PORT 31234
#define  BACKLOG 10
#define  MAXDATASIZE 100
void getWeather(char* day, char* info_buffer){
    if(strcmp(day,"Monday")==0){
        strcpy(info_buffer,"20 degree, cloudy\n");
    }
    if(strcmp(day,"Tuesday")==0){
        strcpy(info_buffer,"22 degree, Sunnny\n");
    }
    if(strcmp(day,"Wednesday")==0){
        strcpy(info_buffer,"24 degree, Rainy\n");
    }
    if(strcmp(day,"Thursday")==0){
        strcpy(info_buffer,"25 degree, Sunny\n");
    }
    if(strcmp(day,"Friday")==0){
        strcpy(info_buffer,"27 degree, Snow\n");
    }
    if(strcmp(day,"Saturday")==0){
        strcpy(info_buffer,"29 degree, cold\n");
    }
    if(strcmp(day,"Sunday")==0){
        strcpy(info_buffer,"10 degree, Rainy\n");
    }
    info_buffer[strlen(info_buffer)]='\0';
}
int main(){
    int  socketfd, buf_len;
    struct  sockaddr_in server;
    struct  sockaddr_in client;
    socklen_t  addrlen;
    char  buf[MAXDATASIZE];
    char weather_info[MAXDATASIZE];


    addrlen =sizeof(client);

    memset(&server, 0, sizeof(server));
    server.sin_family=AF_INET;
    server.sin_port=htons(PORT);
    server.sin_addr.s_addr= htonl (INADDR_ANY);

    if((socketfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
        perror("Creating  socket failed.");
        exit(1);
    }
  
    if(bind(socketfd, (struct sockaddr *)&server, sizeof(server)) == -1) {
        perror("Bind failed.");
        exit(1);
    }   

    while(1){
        if((buf_len = recvfrom(socketfd,buf,MAXDATASIZE,0,(struct sockaddr*)&client,&addrlen)) == -1){
        printf("recv() error\n");
        exit(1);
        }
        buf[buf_len]='\0';
        printf("buffer received is: %s\n",buf);
        getWeather(buf,weather_info);
       
        sendto(socketfd,weather_info,strlen(weather_info),0,(struct sockaddr*)&client,addrlen);
    }
    close(socketfd);
    return 0;
}
