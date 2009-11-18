#include "bovver.h"

#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

/* This is intended to be used multi-threaded so each thread will need a context to run in */

#define BOVVER_HANDLES	10
struct bovver_context {
	int bovverType;
	int threadId;
	char baseDir[200];
	int h[BOVVER_HANDLES];
	DIR *dirH;
	int opMax;
	int op;
	int cycle;
};

void * bovver_init(int threadId, const char *baseDir, int bovver_type)
{
	struct bovver_context *bc = malloc(sizeof(struct bovver_context));
	
	if(bc){
		memset(bc,0,sizeof(*bc));
		bc->threadId = threadId;
		strncpy(bc->baseDir,baseDir,200);
		bc->bovverType = bovver_type;
		bc->opMax = 99;
		printf("bovver_init %d \"%s\"\n",threadId,baseDir);
	}
	return (void *)bc;
}

void bovver_quit(void *x)
{
}

void bovver_do_A(void *x)
{
	struct bovver_context *bc = (struct bovver_context *)x;

	int i;
	int op;
	int pos;
	int n;
	int n1;
	
	char name[200];
	char name1[200];
	
	int start_op;
	
	
	i = rand() % BOVVER_HANDLES;
	op = rand() % bc->opMax;
	pos = rand() & 20000000;
	n = rand() % 100;
	n1 = rand() % 100;
	
	start_op = op;
		
	sprintf(name, "%s/xx%d",bc->baseDir,n);
	sprintf(name1,"%s/xx%d",bc->baseDir,n1);

	bc->op = op;
	bc->cycle++;
	
	op-=1;
	if(op < 0){
		if(bc->h[i]>= 0){
			close(bc->h[i]);
			bc->h[i] = -1;
		}
		return;
	}

	op-=1;
	if(op < 0){
		if(bc->h[i] < 0)
			bc->h[i] = open(name,O_CREAT| O_RDWR, 0666);
		return;
	}

	op-=5;
	if(op< 0){
		lseek(bc->h[i],pos,SEEK_SET);
		write(bc->h[i],name,n);
		return;
	}

	op-=1;
	if(op < 0){
		unlink(name);
		return;
	}
	op-=1;
	if(op < 0){
		rename(name,name1);
		return;
	}
	op-=1;
	if(op < 0){
		mkdir(name,0666);
		return;
	}
	op-=1;
	if(op < 0){
		rmdir(name);
		return;
	}

	bc->opMax = (start_op - op -1);
	
	return;		
	
}

void bovver_do_B(void *x)
{
	struct bovver_context *bc = (struct bovver_context *)x;
	int n = rand() % 20;
	
	bc->cycle++;

	if(!bc->dirH)
		bc->dirH = opendir(bc->baseDir);

	if(!bc->dirH)
		return;

	if(n == 0){
		closedir(bc->dirH);
		bc->dirH = NULL;
	} else {
		while(n > 1){
			n--;
			readdir(bc->dirH);
		}
	}
}


void bovver_do(void *x)
{
	struct bovver_context *bc = (struct bovver_context *)x;
	if(bc->bovverType == 0)
		bovver_do_A(x);
	else
		bovver_do_B(x);
}

void bovver_stats(void *x, int *cycles, int *lastOp)
{
	struct bovver_context *bc = (struct bovver_context *)x;
	
	if(x && cycles)
		*cycles = bc->cycle;
	if(x && lastOp)
		*lastOp = bc->op;

}

