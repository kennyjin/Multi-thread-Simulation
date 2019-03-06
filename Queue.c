/*
	Name: Ying Zhang, Kenny Jin
	NetID: yzhang865, jjin59
	CS login: yingzhang, kjin
*/

#include "Queue.h"

/*
	This file contains the Queue data structure used to store arrays 
	of pointers of lines. It will do enqueue, dequeue and print queue
	statistics.
*/

/*
	Dynamically allocate a new Queue structure and initialize it with 
	an array of character points of length size. That means you'll malloc 
	the queue structure and then malloc the char * array pointed to from 
	that structure. Also remember to any state and synchronization variables used in this structure.
	The function returns a pointer to the new queue structure.
	For testing purposes, create your Queue's with a size of 10.
*/

Queue *CreateStringQueue(int size) {

    Queue *q;
	q = (Queue *)malloc(sizeof(Queue));
	// count of numbers inside queue
    q->sizeq = 0; 
    q->front = 0;
    // End index of the queue
    q->rear = -1;
    q->capacity = size;
	q->enqueueCount = 0;
	q->dequeueCount = 0;
	q->enqueueBlockCount = 0;
	q->dequeueBlockCount = 0;
    q->arrays = (char **)malloc(sizeof(char*)*size);

    // Initialize the mutex for lock use
    pthread_mutex_init(&(q->mutex), NULL);
     
    // Initialize the condition monitor: empty
    if(pthread_cond_init(&(q->empty), NULL) != 0) {
       	fprintf(stderr, "pthread_cond_init error\n");
       	exit(1);
    }
    // Initialize the condition monitor: full
	if(pthread_cond_init(&(q->full), NULL) != 0) {
        fprintf(stderr, "pthread_cond_init error\n");
        exit(1);
    }

	return q;
}

/*
	This function places the pointer to the string at 
	the end of queue q. If the queue is full, then this 
	function blocks until there is space available.
*/
void EnqueueString(Queue *q, char *string) {

	// Lock the mutex 
	pthread_mutex_lock(&(q->mutex));
	// When the queue is full put the string into wait condition
	// and release the mutex lock
	while(q->sizeq == q->capacity) {
		q->enqueueBlockCount++;
		pthread_cond_wait(&(q->full), &(q->mutex));
    }
	q->sizeq++;
	q->rear++;
	// Round up the queue, when we need to append the string at the 
	//end of the queue but the index of the rear ups to the capacity
	if(q->rear == q->capacity) {
		q->rear = 0;
	}
	// Push the string to the end of the queue
	(q->arrays)[q->rear] = string;
	q->enqueueCount++;
	
	// Now queue is not empty, signal DequeueString
	pthread_cond_signal(&(q->empty));
    pthread_mutex_unlock(&(q->mutex));
}

char * DequeueString(Queue *q) {

	pthread_mutex_lock(&(q->mutex));
	// If the queue is empty, put into wait and release the lock
	while(q->sizeq == 0) {
		q->dequeueBlockCount++;
		pthread_cond_wait(&(q->empty), &(q->mutex));
	}
	
	// Get the dequeued string
	char * ret = q->arrays[q->front];
	q->sizeq--;
	q->front++;

	// Round up the queue, when we need to append the string at the 
	//end of the queue but the index of the rear ups to the capacity
	if(q->front == q->capacity) {
		q->front = 0;
	}
	q->dequeueCount++;
	
	// Now queue is not full, signal EnqueueString 
	pthread_cond_signal(&(q->full));
    pthread_mutex_unlock(&(q->mutex));

	return ret;
}

/*
	This function prints the statistics for this queue 
	(see the next section for details).
*/
void PrintQueueStats(Queue *q) {
	fprintf(stderr, "EnqueueCount is: %d\n", q->enqueueCount - 1);
	fprintf(stderr, "DequeueCount is: %d\n", q->dequeueCount - 1);
	fprintf(stderr, "EnqueueBlockCount is: %d\n", q->enqueueBlockCount);
	fprintf(stderr, "DequeueBlockCount is: %d\n", q->dequeueBlockCount);
}


