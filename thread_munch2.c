/*
	Name: Ying Zhang, Kenny Jin
	NetID: yzhang865, jjin59
	CS login: yingzhang, kjin
*/

#include "thread_munch2.h"

/*
	Munch2 will scan the line and convert all lower case letters to upper case 
	(e.g., convert "a" to "A"). It will then pass the line to thread Writer though 
	yet another queue of character strings.
*/
void *thread_munch2(void*pointer_to_Queue23) {
	
	Queue **array_ptr_m2 = (Queue**)pointer_to_Queue23;
	// This is queue2
	Queue *pointer_munch2 = array_ptr_m2[0];
	// This is queue3
	Queue *pointer_munch3 = array_ptr_m2[1];

	while(1) {
		char *string = DequeueString(pointer_munch2);
		if(string == NULL) {
			EnqueueString(pointer_munch3, NULL);
			pthread_exit(NULL);
		}
		int len = strlen(string);
		for(int i = 0; i<len; i++) {
			int c = *(string+i);
			// islower determines the current character
			if(islower(c) >= 0) {
				*(string+i)  = toupper(c);
			}

		}

		EnqueueString(pointer_munch3, string);
	}


}
