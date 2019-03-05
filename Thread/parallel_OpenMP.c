#include <omp.h>
#include<stdio.h>

int main(){

    // execute as much time as it has with you CPU core numbers
    #pragma omp parallel
    {
        printf("I am a parallel region");
    }

    return 0;
}