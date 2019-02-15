#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define BUF_SIZE 3

int buffer[BUF_SIZE];
int add = 0 ;
int rem = 0;
int num = 0;


pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c_cons = PTHREAD_COND_INITIALIZER;
pthread_cond_t c_prod = PTHREAD_COND_INITIALIZER;

void *producer (void *param);
void *consumer (void *param);


int main(int argc,char *argv[]){
    pthread_t tid1, tid2; //thread identifiers
    int i;

    if (pthread_create(&tid1,NULL,producer,NULL)  !=0){
        fprintf(stderr,"Unable to create producer thread\n");
        exit(1);
    }

    if (pthread_create(&tid2, NULL, consumer, NULL) != 0){
        fprintf(stderr,"Unable to create consumer thread\n");
    }


    pthread_join(tid1,NULL);// wait for producer to eixt
    pthread_join(tid2, NULL);// wait for consumer to exit
    printf("Parent quiting\n");
}

void *producer(void *param){
    int i;
    for (i = 1; i <= 20; i++){
        pthread_mutex_lock(&m);
        if (num > BUF_SIZE){ // overflow
            exit(1);
        }
        while (num == BUF_SIZE){ // block if buffer is full
            pthread_cond_wait(&c_pord,&m);
        }

        buffer[add] = i; //buffer not full, so add element
        add = (add + 1) % BUF_SIZE;
        num ++;


        pthread_mutex_unlock(&m);
        pthread_cond_signal(&c_cons);
        printf("producer: inserted %d\n",1);
        fflush(stdout);
    }

    printf("producer: inserted %d\n",i);
    fflush(stdout);
}