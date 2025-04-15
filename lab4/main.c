#include <stdio.h>
#include <stdlib.h>

// self added
#include <unistd.h> // sleep
#include <pthread.h> // thread
#include "bounded_buffer.h"
// #include "bounded_buffer_ns.h"
#define bSIZE 5
#define pNUM 3
#define cNUM 2
#define ITEMS 10

struct bounded_buffer queue;

void *producer(void *ptr);
void *consumer(void *ptr);

int main() {
    /* initialize the queue */
	bounded_buffer_init(&queue, bSIZE);

    /* create producer and consumer threads */
	pthread_t pProducer[pNUM];
	pthread_t pConsumer[cNUM];
    int pID[pNUM];
	int cID[cNUM];

	// create producer threads
	for (int i = 0; i < pNUM; i++) {
		pID[i] = i;
		pthread_create(&pProducer[i], NULL, producer, &pID[i]);
	}

	// create consumer threads
	for (int i = 0; i < cNUM; i++) {
		cID[i] = i;
		pthread_create(&pConsumer[i], NULL, consumer, &cID[i]);
	}

	//wait for producers to finish
	for(int i = 0; i < pNUM; i++){
		pthread_join(pProducer[i], NULL);
	}

	// Push a NULL for each consumer to signal them to terminate
	for (int i = 0; i < cNUM; i++) {
		bounded_buffer_push(&queue, NULL);
	}

	//wait for consumers to finish 
	for (int i = 0; i < cNUM; i++) {
		pthread_join(pConsumer[i], NULL);
	}
	printf("Exiting");

	// destroy buffer
	bounded_buffer_destroy(&queue);

    return 0;
}

/* this is the function executed by the producer thread. 
   It should generate a number of messages and push them into the queue */
void *producer(void *ptr){

	int id = *(int *) ptr;

	for (int i = 0; i < ITEMS; i++) {
		// allocate space for item
		int *item = malloc(sizeof(int));
		
		// assign item a value
		*item = id + i;

		printf("producer %d: producing %d\n", id, *item);
		// push to buffer
		bounded_buffer_push(&queue, item);	
		sleep(2);
	}
    return NULL;
}

/* this is the function executed by the consumer thread. 
   It should pop messages from the queue and print them */
void *consumer(void *ptr){

	int id = *(int *) ptr;

    while (1) {
		// pop message out from buffer
    	int *item = (int*) bounded_buffer_pop(&queue);
	
		if (item != NULL) {	
			printf("\tconsumer %d: consumed %d\n", id, *item);
			// free memory
			free(item);
		} else {
			printf("\tconsumer %d: stop\n", id);
			break;
		}
		
    }
	return NULL;
}
