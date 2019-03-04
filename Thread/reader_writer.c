#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_NUM 10

int X = 0; // Global var for read and wrtie
int resource_counter = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER; //initialize the mutex
pthread_cond_t c_read = PTHREAD_COND_INITIALIZER; //initialize the conditional var for reader
pthread_cond_t c_write = PTHREAD_COND_INITIALIZER; //intialize the conditional var for writer


void *reader(void *param);
void *writer(void *param);



int main(int argc, char* argv[]){

    // Seed the random number generator
	srandom((unsigned int)time(NULL));

    pthread_t thread_array[THREAD_NUM]; // first 5 for reader, last 5 for writer
    for (int i =0;i < THREAD_NUM/2; i++){ // create reader thread
        if (pthread_create(&thread_array[i],NULL,reader,NULL) !=0 ){
            fprintf(stderr,"Unable to create reader thread #%d\n",i);
            exit(1);
        }
    }


    for (int i = THREAD_NUM/2; i < THREAD_NUM;i++){ // create writer thread
        if (pthread_create(&thread_array[i],NULL,writer,NULL) != 0){
            fprintf(stderr,"Unable to create writer thread #%d\n",i);
            exit(1);
        }
    }

    // join the threads
    for (int i = 0; i < THREAD_NUM; i ++){
        pthread_join(thread_array[i],NULL);
    }

    printf("Parent quitting\n");

    return 0;
}


void *reader(void * param){
    usleep(1000 * random());
    for (int i =0; i < 5; i ++){
        pthread_mutex_lock(&m);
            while ( resource_counter == -1){ // it is writing
                pthread_cond_wait(&c_read,&m);
            }
            resource_counter ++;


        pthread_mutex_unlock(&m);


        
        int read_value = X;
        printf("value read is %d, %d readers present\n",read_value,resource_counter);

        pthread_mutex_lock(&m);
            resource_counter --;
            if (resource_counter == 0){
                pthread_cond_signal(&c_write);
            }

        pthread_mutex_unlock(&m);
    }

    printf("reader quitting\n");
    fflush(stdout);
    return 0;
}

void *writer(void *param){
    usleep(1000* random());
    for (int i = 1; i <= 5; i++){
        pthread_mutex_lock(&m);
            while( resource_counter != 0 ){
                pthread_cond_wait(&c_write,&m);
            }
            resource_counter --;
        pthread_mutex_unlock(&m);

        
        X = i;
        printf("value written %d, %d readers present\n",i,resource_counter +1);

        pthread_mutex_lock(&m);
            resource_counter = 0;
            pthread_cond_broadcast(&c_read);
            pthread_cond_signal(&c_write);

        pthread_mutex_unlock(&m);

    }
    printf("writer quitting\n");
    fflush(stdout);
    return 0;
    

}

