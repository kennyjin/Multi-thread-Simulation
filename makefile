CC = gcc
WARNING_FLAGS = -Wall -Wextra
EXE = prodcomm
SCAN_BUILD_DIR = scan-build-out

all: main.o Queue.o thread_reader.o thread_munch1.o thread_munch2.o thread_writer.o
	$(CC) -o $(EXE) main.o Queue.o thread_reader.o thread_munch1.o thread_munch2.o thread_writer.o -lpthread

main.o: main.c Queue.h thread_reader.h thread_munch1.h thread_munch2.h thread_writer.h
	$(CC) $(WARNING_FLAGS) -c main.c -lpthread

Queue.o: Queue.c Queue.h
	$(CC) $(WARNING_FLAGS) -c Queue.c -lpthread

thread_reader.o: thread_reader.c thread_reader.h
	$(CC) $(WARNING_FLAGS) -c thread_reader.c -lpthread

thread_munch1.o: thread_munch1.c thread_munch1.h
	$(CC) $(WARNING_FLAGS) -c thread_munch1.c -lpthread

thread_munch2.o: thread_munch2.c thread_munch2.h
	$(CC) $(WARNING_FLAGS) -c thread_munch2.c -lpthread

thread_writer.o: thread_writer.c thread_writer.h
	$(CC) $(WARNING_FLAGS) -c thread_writer.c -lpthread

clean:
	rm $(EXE) *.o

scan-build: clean
	scan-build -o $(SCAN_BUILD_DIR) make

scan-view: scan-build
	firefox -new-window $(SCAN_BUILD_DIR)/*/index.html 