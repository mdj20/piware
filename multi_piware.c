#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

// globals 
int SIZE_OF_BUFFER = 1024;
int NUM_THREADS = 3;
int PTHREAD_STACK_SIZE = 0;  // not used

// thread function declaration
void *down_work(void *);


// struct for buffer info
typedef struct _buffer_data {
  void* buffer_addr;
  int   buffer_size;
  
} buffer_data;
 
// worker arguments 
typedef struct _worker_thread_data {
  int n;
} worker_thread_data; 


// debbuger/driver for the buffer frames
int main(int argc , char* argv[]){
  
  void *uplink_buffer, *downlink_buffer;
  int up_n=0,down_n=0,i=0,j=0;

  // Allocate buffers and set to zero
  uplink_buffer = (void *) malloc(SIZE_OF_BUFFER);
  downlink_buffer = (void *) malloc(SIZE_OF_BUFFER);
  memset(uplink_buffer,0,SIZE_OF_BUFFER);
  memset(downlink_buffer,0,SIZE_OF_BUFFER);

  pthread_t threads[NUM_THREADS];
  worker_thread_data *d_structs[NUM_THREADS];

  //pthread_t *test_t = 
  for(i=0;i<NUM_THREADS;i++){
    d_structs[i] = malloc(sizeof(worker_thread_data));		      
    d_structs[i]->n = i;				      
    pthread_create(&threads[i],NULL,down_work,d_structs[i]);
  }

  for(i=0;i<1000000;i++){
    j++;
  }

  printf("this is the number: %d\n",j);

  sleep(2);

  void **ret = malloc(sizeof(int));

  for(i=0;i<NUM_THREADS;i++){
    //    printf("thread num: %d\n",threads[i]);
  }

  for(i=0;i<NUM_THREADS;i++){
    pthread_join(threads[i],ret);
  }
}


// worker thread function
void *down_work(void *args){
  worker_thread_data *data = (worker_thread_data*)args;
  printf("thread value n: %d\n",data->n);
  int ret = data->n;
  int i;
  for(i=0;i<10000;i++){
    ret++;
  }
  printf("thread value n: %d\n",ret);
  pthread_exit(&ret);
}


// this thread will fill the buffers so simulte a stream of data / packets etc
void *buffer_filler(void* args){







}




