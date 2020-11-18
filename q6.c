#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

pthread_mutex_t forks[5];
pthread_cond_t cond_var[5];
int state[5];
int i;
pthread_attr_t atribute;
void *fun(int n){
	state[n]=1;	
	// printf("Phillosopher thinking : %d\n",n);
	sleep(2);
	int fork1=n;
	int fork2=(n+1)%5;

	pthread_mutex_lock(&forks[fork1]);
    pthread_mutex_lock(&forks[fork2]);

	while (state[n]==0 || state[fork2]==0)
	{
        if(state[fork1]==0)
	        pthread_cond_wait(&forks[fork1],&cond_var[fork1]);
        else
	pthread_cond_wait(&forks[fork2],&cond_var[fork2]);

	}
printf("P%d recieves F%d,F%d \n",n,fork1,fork2);

state[n]=0;
// printf("%d is now eating \n",n);
sleep(2);

printf("P%d is done eating \n",n);
state[n]=1;
pthread_cond_signal(&cond_var[fork1]);
pthread_mutex_unlock(&forks[fork1]);
pthread_cond_signal(&cond_var[fork2]);
pthread_mutex_unlock(&forks[fork2]);
}

int main(void) {
	pthread_t philosopher[5];
	pthread_attr_init(&atribute);
	int k;
	for(int i=0;i<5;i++){
		k= pthread_mutex_init(&forks[i],NULL);
		if(k==-1){
			printf("unable to initialise\n");
			exit(1);
		}
	}
for(i=0;i<5;i++){
		int k= pthread_cond_init(&cond_var[i],NULL);
		if(k!=0){
			// printf("unable to initialise");
			exit(1);
		}
	}
for(i=0;i<5;i++){
		k= pthread_create(&philosopher[i],NULL,fun,i);
		if(k!=0){
			printf("unable to create thread\n");
			exit(1);
		}
	}
for(i=0;i<5;i++){
		int k= pthread_join(philosopher[i],NULL);
		if(k!=0){
			printf("unable to join\n");
			exit(1);
		}
	}

	return 0;
}
