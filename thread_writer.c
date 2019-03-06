/*
	Name: Ying Zhang, Kenny Jin
	NetID: yzhang865, jjin59
	CS login: yingzhang, kjin
*/

#include "thread_writer.h"

/*
	This thread_writer function prints everything inside queue
*/

void *thread_writer(void *pointer_to_writer) {

	// used to count the number of strings inside queue
	int counter = 0; 
	Queue * queue_writer = (Queue*)pointer_to_writer;
	
	while(1) {
		char * string = DequeueString(queue_writer);
		if(string == NULL) {
			fprintf(stdout, "Total number of strings: %d\n", counter);
			pthread_exit(NULL);
		}
		counter++;
		fprintf(stdout, "%s\n", string);
		free(string);
	}

}
