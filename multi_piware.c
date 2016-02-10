#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

// globals 
int SIZE_OF_BUFFER = 1024;
int NUM_WORKERS = 0;
int PTHREAD_STACK_SIZE = 0;  // not used

// thread function declaration
void *down_work(void *);
void *buffer_filler(void* args);



// header for any structure in the buffer
typedef struct _buffer_element_header {

  char instruction;  // indicates what kind of message buffer item is
  int size;  // indicates size of buffer message

} buffer_element_header;

// struct for buffer info
typedef struct _buffer_thread_data {
  void *buffer_addr;
  int buffer_size;
  pthread_mutex_t buf_mutex;
  char run_flag;
} buffer_thread_data;
 
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

  pthread_t buffer_threads[2];
  buffer_thread_data *b_structs[2];

  // launch buffer thread
  // create struct
  b_structs[0] = malloc(sizeof(buffer_thread_data));
  b_structs[0]->buffer_addr = uplink_buffer;
  b_structs[0]->buffer_size = 0;
  pthread_mutex_init(&(b_structs[0]->buf_mutex),NULL);
  b_structs[0]->run_flag = 1;

  pthread_create(&buffer_threads[i],NULL,buffer_filler,b_structs[0]);

  pthread_t worker_threads[NUM_WORKERS];
  worker_thread_data *d_structs[NUM_WORKERS];

  //pthread_t *test_t = 
  for(i=0;i<NUM_WORKERS;i++){
    d_structs[i] = malloc(sizeof(worker_thread_data));		      
    d_structs[i]->n = i;				      
    pthread_create(&worker_threads[i],NULL,down_work,d_structs[i]);
  }

  sleep(2);
 
  b_structs[0]->run_flag = 0;
  pthread_join(buffer_threads[0], NULL);
  printf("retval: %d\n",b_structs[0]->buffer_size);

  for(i=0;i<NUM_WORKERS;i++){
    pthread_join(worker_threads[i],NULL);
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

  // parse args
  buffer_thread_data *bufdat = (buffer_thread_data*)args;
  

  int n = 0; // number of RUNS

  // run
  while(bufdat->run_flag){
    printf("BUFFER THREAD RUNNING....\n");
    n++;
    //    sleep(1);
  }

  printf("inside: %d\n",n);

  // set size as return value
  bufdat->buffer_size = n;
  // exit thread no return value in pthread
  pthread_exit(NULL);

}




