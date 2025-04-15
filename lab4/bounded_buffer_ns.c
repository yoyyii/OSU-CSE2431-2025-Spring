#include "bounded_buffer_ns.h"
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
	buffer->bufferData = malloc(sizeof(void *) * size);

	if(!buffer->bufferData) {
		printf("memory allocation failed\n");
		exit(1);
	}
}

void bounded_buffer_push(struct bounded_buffer *buffer, void *item){

	// print error if reach max buffer capacity
	if(buffer->count == buffer->bufferSize) {
		printf("push error\n");
		exit(1);
	}

	//add new buffer into tail
	buffer->bufferData[buffer->tail] = item;
		
	// update index of tail. This implementation ensure that once tail reached end of buffer, it comes back to index 0 rather than going out of bound
	buffer->tail = (buffer->tail + 1) % buffer->bufferSize;

	// increase count by 1
	buffer->count += 1;
}

void* bounded_buffer_pop(struct bounded_buffer *buffer){
	
	// return error if empty buffer
	if (buffer->count == 0) {
	    printf("pop error\n");
	    exit(1);
	}	    

	// pop head out from buffer
	void *item = buffer->bufferData[buffer->head];

	// update index of tail. This implementation ensure that once tail reached end of buffer, it comes back to index 0 rather than going out of bound
	buffer->head = (buffer->head + 1) % buffer->bufferSize;
	
	// decrease count by 1
	buffer->count -= 1;
	
	return item;
}

void bounded_buffer_destroy(struct bounded_buffer *buffer){
	// free buffer
	free(buffer->bufferData);
}