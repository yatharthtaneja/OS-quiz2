#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<fcntl.h>

#define PORT 8080
#define MAXLINE 1024
#define BUFSIZE 1

int main(){
    int sockfd;
    // char buffer[500];
    struct sockaddr_in servaddr;
    if((sockfd= socket(AF_INET,SOCK_DGRAM,0))<0){
        perror("Socket creation :");
        exit(1);
    }

    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family =AF_INET;
    servaddr.sin_addr.s_addr=INADDR_ANY;
    servaddr.sin_port = htons(PORT);
int fd;
    if((fd=open("para2.txt",O_RDONLY))<0)
    {
        perror(" Unable");
        exit(1);
    }
char buffer;
int count=0;
int k=0;
char data[500];
char *token ="hellooo ";

while(read(fd,&buffer,BUFSIZE)>0)
 {   
     if (buffer==' ' || buffer == '\n' || buffer=='\0')
     {  
        data[k]='\0';
        // strcpy(token,data);
        int a= sendto(sockfd,(const char *)data,strlen(data),MSG_CONFIRM,(const struct sockaddr *)&servaddr,sizeof(servaddr));

        strcpy(data,"");
        k=0;
     }
     else{   
     data[k]=buffer;
     k++;
    
     }
 }
        //   printf("ENDOFFILe");
data[k]='\0';
// strcpy(token,data);
int a= sendto(sockfd,(const char *)data,strlen(data),MSG_CONFIRM,(const struct sockaddr *)&servaddr,sizeof(servaddr));
strcpy(data,"");
k=0;
strcpy(data,"\n\n");
a= sendto(sockfd,(const char *)data,strlen(data),MSG_CONFIRM,(const struct sockaddr *)&servaddr,sizeof(servaddr));

close(sockfd);
 return 0;   
}