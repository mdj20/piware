#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

// globals 
int SIZE_OF_BUFFER = 1024;
int MIN_BUFFER = 200;
int NUM_WORKERS = 3;
int PTHREAD_STACK_SIZE = 0;  // not used
int MAX_MSG  = 128;
int MIN_MSG  = 32;
float MAX_RAND = .9 , LAMBDA = .3;   // used for probability simulation


// thread function declaration
void *buffer_filler(void* args);
void *worker(void *args);


// header for any structure in the buffer
typedef struct _buffer_element_header {

  char instruction;  // indicates what kind of message buffer item is
  int size;  // indicates size of buffer message

} buffer_element_header;

// struct for buffer info
typedef struct _buffer_thread_data {
  void *buffer_addr;
  int buffer_size;
  pthread_mutex_t *buffer_mutex;
  char run_flag;
} buffer_thread_data;
 
// worker arguments 
typedef struct _worker_thread_data {
  buffer_thread_data *bufdat[2];
  char run_flag;
} worker_thread_data; 


// debbuger/driver for the buffer frames
int main(int argc , char* argv[]){


  int t = 3;

  // argument sets runtime
  if (argc > 1){
    t = (unsigned int)*argv[1];
  }
  
  void *uplink_buffer, *downlink_buffer;
  int up_n=0,down_n=0,i=0,j=0;

  // Allocate buffers and set to zero
  uplink_buffer = (void *) malloc(SIZE_OF_BUFFER);
  downlink_buffer = (void *) malloc(SIZE_OF_BUFFER);
  memset(uplink_buffer,0,SIZE_OF_BUFFER);
  memset(downlink_buffer,0,SIZE_OF_BUFFER);

  pthread_t buffer_threads[2];
  buffer_thread_data *b_structs[2];

  // launch buffer threads
  // create struct uplink
  b_structs[0] = malloc(sizeof(buffer_thread_data));
  b_structs[0]->buffer_addr = uplink_buffer;
  b_structs[0]->buffer_size = 0;
  b_structs[0]->buffer_mutex =  malloc(sizeof(pthread_mutex_t));
  pthread_mutex_init(b_structs[0]->buffer_mutex,NULL);
  b_structs[0]->run_flag = 1;

  // create struct downlink
  b_structs[1] = malloc(sizeof(buffer_thread_data));
  b_structs[1]->buffer_addr = downlink_buffer;
  b_structs[1]->buffer_size = 0;
  b_structs[1]->buffer_mutex =  malloc(sizeof(pthread_mutex_t));
  pthread_mutex_init(b_structs[1]->buffer_mutex,NULL);
  b_structs[1]->run_flag = 1;

  for (i=0;i<2;i++){
    pthread_create(&buffer_threads[i],NULL,buffer_filler,b_structs[i]);
    pthread_create(&buffer_threads[i],NULL,buffer_filler,b_structs[i]);
  }

  pthread_t worker_threads[NUM_WORKERS];
  worker_thread_data *d_structs[NUM_WORKERS];

  //pthread_t *test_t = 
  for(i=0;i<NUM_WORKERS;i++){
    d_structs[i] = malloc(sizeof(worker_thread_data));		      
    d_structs[i]->bufdat[0] = b_structs[0];
    d_structs[i]->bufdat[1] = b_structs[1];
    d_structs[i]->run_flag = 1;
    pthread_create(&worker_threads[i],NULL,worker,d_structs[i]);
  }

  sleep(t);
 

  for(i=0;i<NUM_WORKERS;i++){
    d_structs[i]->run_flag = 0;
    pthread_join(worker_threads[i],NULL);
  }

  b_structs[0]->run_flag = 0;
  pthread_join(buffer_threads[0], NULL);
  printf("retval: %d\n",b_structs[0]->buffer_size);

  b_structs[1]->run_flag = 0;
  pthread_join(buffer_threads[1], NULL);
  printf("retval: %d\n",b_structs[1]->buffer_size);

  

}

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

