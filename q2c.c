#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>

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
    int count =2;
    while(count != 0){
    // printf("");
    msgrcv(mid, &message_buffer, sizeof(message_buffer),1,0);
    if(strcmp(message_buffer.text,"\n\n")==0)
        count--;
    else
        printf("%s ",message_buffer.text);
    }
    // if(strcmp(message_buffer.text,"\n\n")==0)
        msgctl(mid,IPC_RMID,NULL);

    
    return 0;
}