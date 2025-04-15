#include <stdio.h>
#include <pthread.h>
#define THREAD_NO 10

//self added
#include <stdlib.h>

void *mythread(void *arg) {
    int *id = (int *)arg;
    printf("my id is %d\n", *id);
    //self added
    free(id);
    return NULL;
}

int main(){
    pthread_t p[THREAD_NO];
    int i = 0;
    for(i=0; i<THREAD_NO; i++){
	// self added
	int *id = malloc(sizeof(int));
        if (id == NULL) {
		perror("malloc failed");
		exit(1);
	}
	*id = i;

	// changed from &i to id
	pthread_create(&p[i], NULL, mythread, id);
    }

    for(i=0; i<THREAD_NO; i++){
	pthread_join(p[i], NULL);
    }
    return 0;
}
