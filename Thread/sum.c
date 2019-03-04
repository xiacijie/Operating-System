#include<pthread.h>
#include<stdio.h>

int sum;// the data is shared by the threads
void *runner(void *param); // threads call this function
int toInt(char[]);

int main(int argc, char * argv[]){
    pthread_t tid;
    pthread_attr_t attr; // set of thread attributes

    if (argc != 2){
        fprintf(stderr, "usage: a.out <integer value>\n");
        return -1;
    }


    if (toInt(argv[1]) < 0){
        fprintf(stderr, "%d must be >= 0\n",toInt(argv[1]));
        return -1;
    }

    //get the default attributes
    printf("====");
    pthread_attr_init(&attr);
    // create tge thread
    pthread_create(&tid,&attr,runner,argv[1]);
    //wait fir the thread to exit
    pthread_join(tid,NULL);

    printf("sun = %d\n",sum);
}

// the thread will begin control in this function
void *runner(void *param){
    int i,upper = toInt(param);
    sum = 0;
    for (i = 1; i <= upper; i ++){
        sum += i;
    }

    pthread_exit(0);
}

int toInt(char a[]) {
  int c, sign, offset, n;
 
  if (a[0] == '-') {  // Handle negative integers
    sign = -1;
  }
 
  if (sign == -1) {  // Set starting position to convert
    offset = 1;
  }
  else {
    offset = 0;
  }
 
  n = 0;
 
  for (c = offset; a[c] != '\0'; c++) {
    n = n * 10 + a[c] - '0';
  }
 
  if (sign == -1) {
    n = -n;
  }
 
  return n;
}