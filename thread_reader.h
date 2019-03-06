#ifndef THREAD_READER_H
#define THREAD_READER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "Queue.h"
#define BUFSIZE 1024
#define qsize 10

void *thread_reader(void*);

#endif


