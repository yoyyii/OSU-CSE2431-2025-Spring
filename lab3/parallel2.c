#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define ARRAY_SIZE 1000000
#define THREAD_NO 10

int sum = 0;

// initialize lock
pthread_mutex_t lock;

// self added
void *mythread (void*arg) {
	int* thread_id = (int *) arg;

	int loop = ARRAY_SIZE / THREAD_NO;
	for (int i = 0; i < loop; i++) {
		// lock sum
		pthread_mutex_lock(&lock);
		sum += thread_id[i];
		pthread_mutex_unlock(&lock);
	}

	return NULL;
}


int main(){

    int num[THREAD_NO][ARRAY_SIZE/THREAD_NO];
    srand(100);
    //initialize arrays
    for(int i=0; i< THREAD_NO; i++){
	for(int j=0; j< ARRAY_SIZE/THREAD_NO; j++){
            num[i][j] = rand() % 100;
	}
    }

    // your code here. Also add more definition if necessary!
    pthread_t threads[THREAD_NO];
    int thread_ids[THREAD_NO];
    pthread_mutex_init(&lock, NULL);

    //create thread
    for (int i = 0; i < THREAD_NO; i++) {
    	//thread_ids[i] = i;
	pthread_create(&threads[i], NULL, mythread, (void *)num[i] );
    }

    // join thread
    for (int i = 0; i < THREAD_NO; i++) {
    	pthread_join(threads[i], NULL);
    }

    // destroy lock
    pthread_mutex_destroy(&lock);

    printf("sum = %d\n", sum);
    return 0;
}
