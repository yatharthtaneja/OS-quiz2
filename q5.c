#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<string.h>

sem_t wrmutex, mutex;
// void* writer_func(void* id);
// void* reader_func(void* id);
int readcnt=0;


void* reader_func(void* id)
{   
    int i = *(int*)id;

    sem_wait(&mutex);
    readcnt++;
    if(readcnt==1)
    sem_wait(&wrmutex);

// read code
    key_t key = ftok("file",65);
    int shmid=shmget(key,1024,0666|IPC_CREAT);
    char *str =(char*) shmat(shmid,(void*)0,0);
    printf("Reader %d is reading %s\n", i, str);

    shmdt(str);
    // shmctl(shmid,IPC_RMID,NULL);
    sem_post(&mutex);

    sem_wait(&mutex);
readcnt--;
if(readcnt==0);
    sem_post(&wrmutex);
sem_post(&mutex);


}

void* writer_func(void* id)
{   
    int i = *(int*)id;
    int rndm = rand()%10;

    sem_wait(&wrmutex);
    printf("Writer %d is writing %d\n", i, rndm);


    // performs write
    key_t key = ftok("file",65);
    int shmid=shmget(key,1024,0666|IPC_CREAT);
    char *str =(char*) shmat(shmid,(void*)0,0);
    // gets(str);
    char num[50];
    sprintf(num,"%d",rndm);
    strcpy(str,num);
    printf("Writer %d wrote %d\n", i, rndm);
    shmdt(str);
    sem_post(&wrmutex);

}



int main()
{

    printf("Input number of readers/writers: \n");
    int n;
    scanf("%d", &n);

    //number of threads
    pthread_t read[n], write[n];
    int id_n[n];


    sem_init(&mutex, 0, 1);
    sem_init(&wrmutex, 0, 1);


    for (int i=0; i<n; i++) 
    {
        id_n[i] = i;
        //reader threads    
        pthread_create(&write[i], NULL, &writer_func, &id_n[i]);
        pthread_create(&read[i], NULL, &reader_func, &id_n[i]);

    }



    for (int i=0; i<n; i++) 
    {
        pthread_join(write[i], NULL);
        pthread_join(read[i], NULL);
    }
    
    key_t key = ftok("file",65);
    int shmid=shmget(key,1024,0666|IPC_CREAT);
    shmctl(shmid,IPC_RMID,NULL);
    sem_destroy(&mutex);
    sem_destroy(&wrmutex);


    return 0;
}
