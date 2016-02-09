#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>


int SIZE_OF_BUFFER = 1024;
int NUM_THREADS = 10;
int PTHREAD_STACK_SIZE = 0;

// worker function declaration
void *down_work(void *args);


// stuct with pointer to buffers
typedef struct _worker_thread_data {

  int n;
  
} worker_thread_data; 


// debbuger/driver for the buffer frames
int main(int argc , char* argv[]){
  
  void *uplink_buffer, *downlink_buffer;
  int up_n=0, down_n=0;

  // Allocate buffers and set to zero
  uplink_buffer = (void *) malloc(SIZE_OF_BUFFER);
  downlink_buffer = (void *) malloc(SIZE_OF_BUFFER);
  memset(uplink_buffer,0,SIZE_OF_BUFFER);
  memset(downlink_buffer,0,SIZE_OF_BUFFER);

  worker_thread_data *wtdata = malloc(sizeof(worker_thread_data));		      
  wtdata->n = 1;				      
  pthread_t threads[NUM_THREADS];

  //pthread_t *test_t = 

  pthread_create(&threads[0],NULL,down_work,wtdata);


}

void *down_work(void *args){

  worker_thread_data *data = (worker_thread_data*)args;

  printf("thread value n: %d\n",data->n);

}
