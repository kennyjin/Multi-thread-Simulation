#ifndef THREAD_WRITER_H
#define THREAD_WRITER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "Queue.h"
#define BUFSIZE 1024
#define qsize 10

void *thread_writer(void *args);

#endif
