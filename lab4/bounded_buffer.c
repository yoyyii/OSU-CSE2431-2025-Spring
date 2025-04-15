#include "bounded_buffer.h"
#include <stdio.h>
#include <stdlib.h>

/*Do not use any global variables for implementation*/

void bounded_buffer_init(struct bounded_buffer *buffer, int size){
	
	// buffer could hold as much as the size
	buffer->bufferSize = size;

	// nothing in buffer yet when we initialize 
	buffer->count = 0;

	// index of head
	buffer->head = 0;

	// index of tail
	buffer-> tail = 0;

	// initialize and allocate space for actual buffer 
	buffer->bufferData = (void **) malloc(sizeof(void *) * size);

	// check memory allocate successfully
	if(!buffer->bufferData) {
		printf("memory allocation failed\n");
		exit(1);
	}

	// initialized mutex and confition variables
	pthread_mutex_init(&buffer->mutex, NULL);
	pthread_cond_init(&buffer->notEmpty, NULL);
	pthread_cond_init(&buffer->notFull, NULL);
}

void bounded_buffer_push(struct bounded_buffer *buffer, void *item){

	// lock mutex
	pthread_mutex_lock(&buffer->mutex);

	// wait until buffer is not full
	while (buffer->count == buffer->bufferSize) {
		pthread_cond_wait(&buffer->notFull, &buffer->mutex);
	}

	//add new buffer into tail
	buffer->bufferData[buffer->tail] = item;
	
	// update index of tail. This implementation ensure that once tail reached end of buffer, it comes back to index 0 rather than going out of bound
	buffer->tail = (buffer->tail + 1) % buffer->bufferSize;

	// increase count by 1
	buffer->count += 1;

	// buffer not empty
	pthread_cond_signal(&buffer->notEmpty);

	// unlock mutex
	pthread_mutex_unlock(&buffer->mutex);
}

void* bounded_buffer_pop(struct bounded_buffer *buffer){
	
	// lock mutex
	pthread_mutex_lock(&buffer->mutex);

	// wait until buffer is not empty
	while (buffer->count == 0) {
		pthread_cond_wait(&buffer->notEmpty, &buffer->mutex);
	}	    

	// pop head out from buffer
	void *item = buffer->bufferData[buffer->head];

	// update index of tail. This implementation ensure that once tail reached end of buffer, it comes back to index 0 rather than going out of bound
	buffer->head = (buffer->head + 1) % buffer->bufferSize;

	// decrease count by 1
	buffer->count -= 1;

	// buffer not full
	pthread_cond_signal(&buffer->notFull);

	// unlock mutex
	pthread_mutex_unlock(&buffer->mutex);
		
	return item;
}

void bounded_buffer_destroy(struct bounded_buffer *buffer){
	
	// free buffer
	free(buffer->bufferData);
	
	// destroy mutex and condition variables
	pthread_mutex_destroy(&buffer->mutex);
	pthread_cond_destroy(&buffer->notEmpty);
    pthread_cond_destroy(&buffer->notFull);

	
}
