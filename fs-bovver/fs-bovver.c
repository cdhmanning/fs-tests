#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/stat.h>

#include "bovver.h"

#define N_THREADS 10
#define BASE_DIR "/mnt/baseDir"

int cycles[N_THREADS];

struct thread_init{
	int n;
	char baseDir[200];
};

void *bovver_thread(void *voidargptr)
{
	struct thread_init *args = (struct thread_init *)voidargptr;
	void *bc = NULL;
	
	bc = bovver_init(args->n, args->baseDir, args->n & 0);
	
	while(bc){
		bovver_do(bc);
		cycles[args->n]++;
	}
	return NULL;
}

void * monitor_thread(void *voidargsptr)
{
	int i;
	int mon=0;
	
	while(1){
		sleep(5);
		mon++;
		printf("%6d",mon);
		for(i = 0; i < N_THREADS; i++)
			printf("%10d",cycles[i]);
		printf("\n");
	}
	
	return NULL;

}


int main()
{
	int i;
	
	pthread_t threads[N_THREADS];
	
	mkdir(BASE_DIR,0666);
	
	for(i = 0; i < N_THREADS; i++){
		struct thread_init *threadInit = malloc(sizeof(struct thread_init));
		threadInit->n = i;
		strcpy(threadInit->baseDir,BASE_DIR);
		pthread_create(&threads[i],NULL,bovver_thread,(void *)threadInit);
	}

	monitor_thread(NULL);	
	
	return 0;
}
