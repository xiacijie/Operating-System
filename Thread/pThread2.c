#include<stdio.h>
#include<pthread.h>
#define NUM_THREADS 4
//possible output
// 0 1 2 3
// 0 2 1 3
// 0 2 2 3 ???????
void *threadFunc(void *pArg){ // thread main
    int *p = (int*) pArg;
    int myNUm = *p;
    printf("Thread number %d\n",myNUm);
    return 0;

}



int main(void){
    int i;
    pthread_t tid[NUM_THREADS];
    for (i = 0; i <NUM_THREADS; i ++){
        pthread_create(&tid[i],NULL,threadFunc, &i);
    }

    for (i = 0; i < NUM_THREADS; i ++){
        pthread_join(tid[i], NULL);
    }
}