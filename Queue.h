#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct queue{

	// current number of elements in the queue
	int sizeq;
	int capacity;
	int front;
	int rear;
	char **arrays;
	int enqueueCount;
	int dequeueCount;
	int enqueueBlockCount;
	int dequeueBlockCount;

	pthread_mutex_t mutex;
    pthread_cond_t empty;
	pthread_cond_t full;

}Queue;

Queue *CreateStringQueue(int size);
void EnqueueString(Queue *q, char *string);
char * DequeueString(Queue *q);
void PrintQueueStats(Queue *q);

#endif
