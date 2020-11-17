#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include<string.h>
#define BUFSIZE 1

struct message_buffer
{
    long type;
    char text[500];
    /* data */
}message_buffer;

int main(){
    key_t key;
    int mid;
    key = ftok("file",65);
    mid= msgget(key,0666 |IPC_CREAT);
    message_buffer.type = 1 ;
    // gets(message_buffer.text);
int fd;
    if((fd=open("para1.txt",O_RDONLY))<0)
    {
        perror(" Unable");
        exit(1);
    }
char buffer;
int count=0;
int k=0;
char data[500];
while(read(fd,&buffer,BUFSIZE)>0)
 {   
     if (buffer==' ')
     {  
        data[k]='\0';
        strcpy(message_buffer.text,data);
        msgsnd(mid, &message_buffer, sizeof(message_buffer),0);
        printf("%s",message_buffer.text);
    
        strcpy(data,"");
        k=0;
     }
     else{   
     data[k]=buffer;
     k++;
    
     }
}
// printf("%s",data[13][3]);

close(fd);

    return 0;
}
