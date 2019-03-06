/*
	Name: Ying Zhang, Kenny Jin
	NetID: yzhang865, jjin59
	CS login: yingzhang, kjin
*/

#include "thread_munch1.h"

/*
	Munch1 will scan the line and replace each space character (not tabs or newlines) 
	with an asterisk ("*") character. It will then pass the line to thread Munch2 through 
	another queue of character strings.
*/

void *thread_munch1(void *pointer_to_Queue12) {
	
	Queue ** array_newptr = (Queue**)pointer_to_Queue12;
	// This is queue1
	Queue *queue_reader = array_newptr[0];
	// This is queue2
	Queue *pointer_munch1 = array_newptr[1];
	char* ptr;
	char change = '*';
	char whitespace = ' ';
	
	while(1) {
		char *string = DequeueString(queue_reader);
		if(string == NULL) {
			EnqueueString(pointer_munch1, NULL);
			pthread_exit(NULL);
		}
	
		// Return the pointer of the first occurrence of whitespace
		ptr = index(string, whitespace);

		while(ptr != NULL) {
		
			*ptr = change;
			ptr = index(ptr+1, whitespace);
		}
		EnqueueString(pointer_munch1, string);
	}
	

}
