CC=gcc
CFLAGS=-I. -pthread

all: parallel_min_max process_memory parallel_sum

parallel_min_max: utils.o find_min_max.o utils.h find_min_max.h parallel_min_max.c
	$(CC) -o parallel_min_max parallel_min_max.c find_min_max.o utils.o $(CFLAGS)

process_memory: process_memory.c
	$(CC) -o process_memory process_memory.c $(CFLAGS)

utils.o: utils.h
	$(CC) -o utils.o -c utils.c $(CFLAGS)

find_min_max.o: utils.h find_min_max.h
	$(CC) -o find_min_max.o -c find_min_max.c $(CFLAGS)

parallel_sum: parallel_sum.c
	$(CC) -o parallel_sum parallel_sum.c $(CFLAGS)

clean:
	rm -f utils.o find_min_max.o parallel_min_max process_memory parallel_sum
