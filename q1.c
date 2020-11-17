#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<ctype.h>

int main(){
    int fd1[2];
    int fd2[2];

    char input[500];
    if(pipe(fd1)==-1 || pipe(fd2)==-1){
        printf("Pipe failed");
        return -1;
    }

    scanf("%[^\n]%*c",input);
    // fgets(input,500,stdin);
    pid_t pid=fork();
    if(pid<0){
        printf("Fork failed");
        return -1;
    }
    else if(pid!=0){
        char buffer[500];
        close(fd1[0]);
        write(fd1[1],input,strlen(input)+1);
        close(fd1[1]);
        waitpid(pid,NULL,0);
        close(fd2[1]);
        read(fd2[0],buffer,500);

        for(int i=0;i<strlen(buffer);i++){
            char a = buffer[i];
            if(a=='\\'){
                char b= buffer[i+1];
                i++;
                if (b=='N')
                    printf("\n");
                else if (b=='A')
                    printf("\a");
                else if (b=='T')
                    printf("\t");
                else if (b=='B')
                    printf("\b");
                else if (b=='R')
                    printf("\r");
                else if (b=='V')
                    printf("\v");
                else if (b=='\'')
                    printf("'");
                else if (b=='\\')
                    printf("\\");
                else if (b=='"')
                    printf("\"");
                else if (b=='?')
                    printf("\?");

                else if (b=='0')
                    printf("\0");
                // else if(b=='o' && buffer[i+1]=='o' && buffer[i+2]=='o')
                // {
                //     i+=2;
                //     printf("\ooo")
                // }
                else
                {
                    printf("%c",b);
                }
                               
            }
            else
            {
                // printf("\n");
                printf("%c",a);
            }
            
        }
        close(fd2[0]);
    }
    else{
        close(fd1[1]);
        char buffer[500];
        read(fd1[0],buffer,500);
        int j=0;
        char ch;
        while (buffer[j])
        {   
            ch= buffer[j];
            buffer[j]=toupper(ch);
            j++;
        }
        
        close(fd1[0]);
        close(fd2[0]);
        write(fd2[1],buffer,sizeof(buffer)+1);
        close(fd2[1]);
        exit(0);
    }
    return 0;
}