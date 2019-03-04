#include<pthread.h>
#include<stdio.h>
#define NUM_THREADS 10

int main(){
    //an array of threads to be joined upon
    pthread_t workers[NUM_THREADS];
    for (int i = 0 ; i < NUM_THREADS; i++){
        pthread_join(workers[i],NULL);
    }
    return 0;
}