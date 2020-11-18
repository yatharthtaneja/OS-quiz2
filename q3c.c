#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#define PORT 8080
#define MAXLINE 1024

int main(){
    int sockfd;
    char buffer[500];
    struct sockaddr_in servaddr , cliaddr;
    if((sockfd= socket(AF_INET,SOCK_DGRAM,0))<0){
        perror("Socket creation :");
        exit(1);
    }

    memset(&servaddr,0,sizeof(servaddr));
    memset(&cliaddr,0,sizeof(cliaddr));
    servaddr.sin_family =AF_INET;
    servaddr.sin_addr.s_addr=INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    if(bind(sockfd,(const struct sockaddr *)&servaddr,sizeof(servaddr))<0){
        perror("binding failed: ");
        exit(1);
    }
    int len = sizeof(cliaddr);
    int count =2;
    while(count!=0){
    int n = recvfrom(sockfd,(char *)buffer,MAXLINE,MSG_WAITALL,(struct sockaddr *)&cliaddr,&len);
    buffer[n]='\0';
    if(strcmp(buffer,"\n\n")==0)
        count--;
    else
    { 
    printf("%s\n",buffer);
    }
    }
 return 0;   
}