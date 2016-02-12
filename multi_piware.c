#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

// globals
int NUM_THREAD = 3;

int NUM_BUFFERS = 2; 
int SIZE_OF_BUFFER = 1024;
int MIN_BUFFER = 200;
int NUM_WORKERS = 3;
int PTHREAD_STACK_SIZE = 0;  // not used
int MAX_MSG  = 128;
int MIN_MSG  = 32;
float MAX_RAND = .9 , LAMBDA = .3;   // used for probability simulation


// thread function declaration
//void *buffer_filler(void* args);
//void *worker(void *args);
//void equals(void* x, void* y){return(*x-*y);}
void *worker_fnc(void *args);

// header for any structure in the buffer
typedef struct _buffer_element_header {
  char instruction;  // indicates what kind of message buffer item is
  int size;  // indicates size of buffer message
} buffer_element_header;
 

typedef struct _thread_data {

  pthread_t worker_thread[NUM_THREAD];
  int work_ctr[NUM_THREAD];
  void *args[NUM_THREAD];
  int ret[NUM_THREAD];
  
} thread_data;

// debbuger/driver for the buffer frames
int main(int argc, char* argv[]){

  int t = 3;

  // argument sets runtime
  if (argc > 1){
    t = (unsigned int)*argv[1];
  }
  
  int up_n=0,down_n=0,i=0,j=0;

  thread_data *control;
  control = malloc(sizeof(thread_data));
  control->args = malloc(sizeof(void*)*NUM_THREADS);

  memset(control->work_ctr,0,sizeof(work_ctr));

  // launch 
  for (i=0;i<NUM_THREAD;i++){
    pthread_create(&(control->worker_thread[i]),NULL,worker_fnc,control);
  }

  sleep(2);

  for(i=0;i<NUM_THREAD;i++){
    pthread_join(control->worker_thread[i],NULL);
  }


  // sleep(t);

  
}

/*
typedef struct _thread_data {

  pthread_t worker_thread[NUM_BUFFERS];
  int work_ctr[NUM_WORKERS];
  void *args[NUM_WORKERS];
  int ret[NUM_WORKERS];
  
} thread_data;
*/

void *worker_fnc(void *args){

  thread_data *data = (thread_data*)args;

  pthread_d self = pthread_self();
  int index=0;
  while(!pthread_equals(self,data->worker_thread[index])){
    index++;
  }

  print("%d %d\n",self,data->worker_thread[index]);
  sleep(index);

}

/*

// worker thread function
void *worker(void *args){

  int i;
  // parse args
  worker_thread_data *threaddat = (worker_thread_data*)args;
  
  while(threaddat->run_flag){

        
    if (threaddat->bufdat[0]->buffer_size < MIN_BUFFER  && threaddat->bufdat[1]->buffer_size < MIN_BUFFER){
      sleep(2);
    }
    else{
      for (i=0;i<2;i++){
	// enter critical

	
	pthread_mutex_lock(threaddat->bufdat[i]->buffer_mutex);
	
   

	if (threaddat->bufdat[i]->buffer_size > MIN_BUFFER){
	  buffer_element_header temp_header;
	  memcpy(&temp_header,threaddat->bufdat[i]->buffer_addr,sizeof(buffer_element_header));
	  
	  printf("s %d\n", temp_header.size);

	  int n_size = threaddat->bufdat[i]->buffer_size - temp_header.size;
	  
	  // copy the rest of the data to the front
	  //memcpy(threaddat->bufdat[i]->buffer_addr,(threaddat->bufdat[i]->buffer_addr + temp_header.size), n_size);
	  
	  threaddat->bufdat[i]->buffer_size = n_size;
	  
	  printf("%d Remove: %d\n",i,n_size);
	  
	}
	
	
	//exit crit
	pthread_mutex_unlock(threaddat->bufdat[i]->buffer_mutex);

	
      }
    }

    
  }
    
  pthread_exit(NULL);
}
*/

/*


// this thread will fill a buffer to simulte a stream of data / packets etc
void *buffer_filler(void* args){

  // parse args
  buffer_thread_data *bufdat = (buffer_thread_data*)args;
  int l_size = bufdat->buffer_size;  // local size
  int n = 0 , i; 

  // allocate msh contruction buffer
  //  void *temp = malloc(MAX_MSG+sizeof()) 

  float p;

  // run can be toggled by calling thread
  while(bufdat->run_flag){    
    // check for full buffer
    if(bufdat->buffer_size < SIZE_OF_BUFFER -(MAX_MSG + sizeof(buffer_element_header))){
      // enter critical
      pthread_mutex_lock(bufdat->buffer_mutex);

      l_size = (rand()%(MAX_MSG-MIN_MSG))+MIN_MSG;
      printf("lsize: %d\n",l_size); //DEBUG PRINT

      buffer_element_header temp_header;
      temp_header.size = l_size+sizeof(buffer_element_header);     // msg size
      temp_header.instruction = 0;  // for now just 0 will determine what needs to be done with message 

      // allocate temp buffer to size (Message size + header size) and add copy header
      char *data = malloc(l_size+sizeof(buffer_element_header));
      memcpy(data,&temp_header,sizeof(buffer_element_header));  //copy heaer to temp buffer

      for(i=0;i<l_size;i++){
	*(data+i+sizeof(buffer_element_header)) = (char)rand()%255; // fill rest of temp buffer
      }

      // copy data from temp buffer to buffer and update size
      memcpy(bufdat->buffer_addr,data,l_size+sizeof(buffer_element_header));
      bufdat->buffer_size+=l_size+sizeof(buffer_element_header);

      // exit critical
      pthread_mutex_unlock(bufdat->buffer_mutex);      

      free(data);

      printf("bsize: %d\n",bufdat->buffer_size);
    }    
    else{
      sleep(1);
    }

    printf("BUFFER THREAD RUNNING....\n");
    n++;
    //    sleep(1);
  }

  printf("inside: %d\n",n);

  // set size as return value
  bufdat->buffer_size = n;
  // exit thread no return value in pthread
  printf("BUFFER EXIT...\n");
  pthread_exit(NULL);
}
*/
