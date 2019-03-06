#ifndef THREAD_MUNCH2
#define THREAD_MUNCH2

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>
#include "thread_munch1.h"
#include "Queue.h"
#define BUFSIZE 1024
#define qsize 10

void *thread_munch2(void *args);

#endif