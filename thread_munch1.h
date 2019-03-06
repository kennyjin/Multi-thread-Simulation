#ifndef THREAD_MUNCH1
#define THREAD_MUNCH1

#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "thread_reader.h"
#include "Queue.h"
#define BUFSIZE 1024
#define qsize 10

void *thread_munch1(void *args);

#endif