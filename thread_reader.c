/*
	Name: Ying Zhang, Kenny Jin
	NetID: yzhang865, jjin59
	CS login: yingzhang, kjin
*/

#include "thread_reader.h"

/*
	The Reader thread will read from standard input, one line at a time. 
	Reader will take the each line of the input and pass it to thread Munch1 
	through a queue of character strings.
*/
void *thread_reader(void *pointer_to_Queue1) {
	
	char c;
	Queue *q = (Queue *)pointer_to_Queue1;
	while(1) {
		char * str = malloc(BUFSIZE * sizeof(char));
		// This is a boolean value, indicating if the input exceeds the length limit
		int exceedSize = 1; 
		for(int i = 0; i < BUFSIZE; i++) {
			// Read each character
			c = fgetc(stdin);
			// If it reaches the end of file
			if (c == EOF) {
				// If it not empty file, enqueue the string
				if (i != 0) {
					EnqueueString(q, str);
				} else {
					free(str); // Important!
				}
				EnqueueString(q, NULL);
				pthread_exit(NULL);
			}
			if (c == '\n') {
				// Put null character to the end of string
				str[i] = '\0'; 
				exceedSize = 0;
				break;
			}
			str[i] = c;
		}
		if (exceedSize == 1)
		{
			free(str); // Important!
			fprintf(stderr, "%s\n", "Input line exceeds the length limit.");
			// The while loop discards the remaining characters of the long string
			while((c = fgetc(stdin)) != '\n')
			{
				// This deals with the situation 
				// where the long line is at the end of file 
				// and does not have a new line character
				if (c == EOF) {
					EnqueueString(q, NULL);
					pthread_exit(NULL);
				}
				continue;
			}
		}
		if (exceedSize == 0)
		{
			EnqueueString(q, str);
		}
	}	


}

