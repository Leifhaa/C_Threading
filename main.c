#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#define COUNT_TO 10000

int glob_count = 0;

//A parameter struct
typedef struct {
    char name[50];
    pthread_mutex_t* mutex;
} counterArgs;


void *printMessage(void* pvData){
    char *pszMessage = (char *)pvData;
    printf("In %s.\n", pszMessage);
    return NULL;
}

void *counter(void* pvData){
    counterArgs *args = (counterArgs*)pvData;
    while (1){
        pthread_mutex_lock(args->mutex);
        if (glob_count >= COUNT_TO){
            pthread_mutex_unlock(args->mutex);
            return NULL;
        }
        glob_count++;
        printf("Thread: %s increased counter to: %d\r\n", args->name, glob_count);
        pthread_mutex_unlock(args->mutex);
    }
}

int main() {
    /*
     * 1. Best practice for threads is to create a STRUCT with arguments for the function,
        all threads take a VOID *, and the first thing we do in the thread is to typecast this to
        our “parameter struct”.
     */
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    counterArgs *args1;
    args1 = (counterArgs *) malloc(sizeof(counterArgs));
    strcpy(args1->name, "foo");
    args1->mutex = &mutex;

    counterArgs *args2;
    args2 = (counterArgs *) malloc(sizeof(counterArgs));
    strcpy(args2->name, "bar");
    args2->mutex = &mutex;
    /*
    2. All synchronization variables should be INITIALIZED by the caller, and put into this
    struct – do not use global variables.
     */
    pthread_t pThread1, pThread2;
    printf("Before threads started\r\n");

    pthread_create(&pThread1, NULL,counter, (void *) args1);
    pthread_create(&pThread2, NULL,counter, (void *) args2);
    printf("After threads has started!\n");

    ///Wait for thread to finish
    //3. Always wait for threads using JOIN before closing
    pthread_join(pThread1, NULL);
    pthread_join(pThread2, NULL);
    printf("After threads has finished");

    free(args1);
    free(args2);

    return 0;
}
