#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>
#include "recorder.h"

// global determine how 
int NUM_THREAD = 5;   // number of total threads  must be >= NUM_BUFFERS
int NUM_BUFFERS = 2; // number of threads use to fill buffers 
int SIZE_OF_BUFFER = 1024;  // size of allocated buffer 
int MIN_BUFFER = 0;      // minimum buffer content for messages to be pulled form buffer
int MAX_MSG  = 128;      //  maximun size of message
int _RECORD = 1;

// header for any structure in the buffer each msg in the buffer will begin with this.
typedef struct _buffer_element_header {
  char instruction;  // indicates what kind of message buffer item is hypothetically 
  int size;  // indicates size of buffer message
} buffer_element_header;
  
// buffer data 
typedef struct _buffer_data_struct {
  char* buff;  // buffer address
  pthread_mutex_t mutex; // buffer mutex
  int size;   // size of all data in buffer
} buffer_data_struct ; 
 
// this structure was going to be used for additional arguments or or funtion pointers to threads, not implimented
typedef struct _thread_args {
  void* ptr;
} thread_args;

typedef struct _thread_data {
  int n_thread;  // total number of threads 
  pthread_t *worker_thread;  // threads data type 
  int *work_ctr;  // thread control variable 
  int *args;      // additional thread aguments
  int *ret;       // return value or status variable 
  buffer_data_struct *buffers;  // buffer data
} thread_data;

// function prototypes
void *worker_fnc(void *params);
int c0(int index, int arg, thread_data *control);
int c1(int index,int arg,  thread_data *control);
void c2(int index,int arg, thread_data *control);
int add_msg(void* buff, int b_size);
int get_msg(buffer_data_struct *bufdat, char* msg);
void put_msg(int i ,int x, int y);

int main(int argc, char** argv){
  int t = 3; // defult run value

  // argument sets run-time
  if (argc > 1){
    t = strtol(argv[1],NULL,0);
  }

  init_recorder(2,500); // init transaction recorder

  int i=0,j=0;

  char *buffer;
  buffer = malloc(SIZE_OF_BUFFER*2);
  
  // allocate space for thread control
  thread_data *control;
  control = malloc(sizeof(thread_data));
  control->worker_thread = malloc(sizeof(pthread_t)*NUM_THREAD);
  control->work_ctr = malloc(sizeof(int)*NUM_THREAD);
  control->args = malloc(sizeof(int)*NUM_THREAD);
  control->ret = malloc(sizeof(int)*NUM_THREAD);
  control->n_thread=0;

  // zero values
  memset(control->work_ctr,0,sizeof(int)*NUM_THREAD);
  memset(control->ret,0,sizeof(int)*NUM_THREAD);
  
  // set buffer data
  control->buffers = malloc(sizeof(buffer_data_struct)*2);
  for (i=0;i<NUM_BUFFERS;i++){
    control->buffers[i].buff = &(buffer[i*SIZE_OF_BUFFER]);
    control->buffers[i].size = 0;
    pthread_mutex_init(&(control->buffers[i].mutex),NULL);
  }

  // launch buffer filler threads
  j = 0; // buffer index
  for (i=control->n_thread;i<(control->n_thread+NUM_BUFFERS);i++){
    control->work_ctr[i] = 0; // code for buffer filler
    control->args[i] = j++;  // code for buffer index / usually just up or down
    pthread_create(&(control->worker_thread[i]),NULL,worker_fnc,control);
  }

  control->n_thread = i;
  printf("number of buffers: %d\n",i);

  // launch MSG handler threads
  j=0;
  for (i=control->n_thread;i<NUM_THREAD;i++){
    control->work_ctr[i]=1;  // indicates to thread that it is a msg handler
    control->args[i] = j++;  // argument for what buffer it should access 
    pthread_create(&(control->worker_thread[i]),NULL,worker_fnc,control);
    if (j==NUM_BUFFERS){
      j=0;
    }
  }
  control->n_thread += i;

  printf("number of workers: %d\n",NUM_THREAD-NUM_BUFFERS);
  printf("Main thread sleeping for %d ... \n ",t );
 
  sleep(t); // 


  // join all threads
  for(i=0;i<NUM_THREAD;i++){
    control->work_ctr[i]=3;
    pthread_join(control->worker_thread[i],NULL);
  }

  //tally results
  int bufferwork=0, workerwork=0;
  for (i=0;i<NUM_BUFFERS;i++){
    bufferwork += control->ret[i];
    printf("BUFFER %d INPUT: %d\n",i,control->ret[i]);
  }
  printf("TOTAL BUFFER INPUT: %d\n", bufferwork);
  
  for (i=NUM_BUFFERS;i<NUM_THREAD;i++){
    workerwork += control->ret[i];
    printf("WORKER %d : %d\n",i,control->ret[i]);
  }
  printf("TOTAL WORKER: %d\n",workerwork);

  int **back;
  back = malloc(sizeof(int*)*2);
  back[0]= malloc(sizeof(int)*3*500);
  back[1]= malloc(sizeof(int)*3*500);
  memcpy(back[0],records(0),sizeof(int)*n(0)*3);
  memcpy(back[1],records(1),sizeof(int)*n(1)*3);
 
  int* ptr;
  ptr = back[0];
  for(i=0;i<500;i++){
    printf("%d %d %d %d \n",i,*ptr,*(ptr+1),*(ptr+2));
    ptr+=3;
  }


}

void *worker_fnc(void *params){
  thread_data *control = (thread_data*)params; // get params
  int total_work = 0; 

  // detrmines what index thread is at in control via linear search through array.
  pthread_t self = pthread_self();
  int index=0;
  while(!pthread_equal(self,control->worker_thread[index])){
    index++;
  }

  //thread control
  for(;;){
    switch(control->work_ctr[index]){
    case 0:   // fill buffer state, buffer filler denoted by int in control->args[index]
      control->ret[index] = 0;
      total_work += c0(index,control->args[index],control);
      break;
    case 1:   // rmove msg from buffer state, buffer denoted by int in control->args[index]
      control->ret[index] = 1;
      total_work += c1(index,control->args[index],control);
      //      usleep(100);
      break;
    case 2:   // debug routine (reads data in buffer and prints and resets total_work)
      _RECORD = 1 ;  // sets recording 
      control->ret[index] = 2;
      c2(index,control->args[index],control);
      int i=0;
      for (i=0;i<25;i++){
	total_work = c1(index,control->args[index],control);
      }
      sleep(5);
      break;
    case 3:   // exit state
      control->ret[index] = total_work; // sets return value to total work done
      pthread_exit(NULL);
      break;
    case 4:   // sleep state
      control->ret[index] = 4;
      sleep(10);
      break;
    }
  }
}

// add data to buffer.
int c0(int index, int arg, thread_data *control ){

  int ret=0;

  buffer_data_struct *bufdat = &(control->buffers[arg]);
  pthread_mutex_lock(&(bufdat->mutex));
  if ( bufdat->size < (SIZE_OF_BUFFER - (MAX_MSG + sizeof(buffer_element_header))) ){
    ret = add_msg(bufdat->buff,bufdat->size); //call add msg
    put_msg(index,arg,ret);

    bufdat->size += ret; //update buffer size
  }  
  pthread_mutex_unlock(&(bufdat->mutex));
  return ret;
}

int c1(int index, int arg, thread_data *control ){

  int ret = 0;

  buffer_data_struct *bufdat = &(control->buffers[arg]);
  char *msg; 
  pthread_mutex_lock(&(bufdat->mutex));
  if ( bufdat->size >  MIN_BUFFER ){
    buffer_element_header *header;
    header = (buffer_element_header*)bufdat->buff;
    msg = malloc(header->size);
    ret = get_msg(bufdat,msg);
  
    // do something with msg etc...


    header = (buffer_element_header*)msg;
    if (_RECORD != 0){
      put_msg(arg,index,-(header->size));
    }

    free(msg);  // 
  }  
  pthread_mutex_unlock(&(bufdat->mutex));
  
  return ret;

}

void c2(int index,int arg, thread_data *control){  // prints contents of buffer 

    buffer_data_struct *bufdat = &(control->buffers[arg]);
    int ptr_index = 0;
    char* ptr;

    pthread_mutex_lock(&(bufdat->mutex));

    printf("Thread transaction Record:\n");



    printf("Buffer: %d  :",arg);
    while (ptr_index < bufdat->size){
      ptr = bufdat->buff+ptr_index;
      buffer_element_header *header = (buffer_element_header*) ptr;
      printf("%d; ",header->size);
      ptr_index += header->size;
    }    
    pthread_mutex_unlock(&(bufdat->mutex));    
}
void c3(int index, thread_data *control ){

  // not implimented 
  
}

// gets msg from buffer denoted by bufdat, char is buffer must be as big as the incoming message
int get_msg(buffer_data_struct *bufdat, char* msg){

  char* buff_ptr;
  buff_ptr = bufdat->buff;
  buffer_element_header *header;
  header = (buffer_element_header*)bufdat->buff;
  int msg_size = header->size;
  memcpy(msg,bufdat->buff,msg_size);         //copy data from buffer to msg buffer

  buff_ptr += msg_size;

  memmove(bufdat->buff,buff_ptr,((bufdat->size)-msg_size)); // shift data to front of buffer
  bufdat->size -= msg_size;

  return msg_size; // return message size

}

int add_msg(void* buff, int b_size){
  int data_size = (rand()%MAX_MSG);          // size of data 
  int msg_size  = data_size+sizeof(buffer_element_header); // size of data+msg header

  char* msg;             // pointer and allocation to base of new message buffer
  msg = malloc(msg_size);

  char* ptr;  // pointer set to msg at point after header
  ptr = msg+sizeof(buffer_element_header); //set pointer offset of header

  // create msg header and copy to msg
  buffer_element_header *header;
  header = malloc(sizeof(buffer_element_header));
  header->size = msg_size;
  header->instruction = 0x0;
  memcpy(msg,header,sizeof(buffer_element_header));  // copy header to beginning of message
  
  // fill rest of msg
  int i;
  for(i=0;i<data_size;i++){
    ptr[i] = (char)i;
  }

  // set pointer to after last message in buffer
  ptr = buff;
  ptr = ptr+b_size;
  // copy msg to buffer
  memcpy(ptr,msg,msg_size);
 
  free(msg);
  free(header);

  return msg_size;
} 

int new_record(int x, int y , int z){
	if (recorder_is_init()){
	int* msg;
	msg = malloc(sizeof(int)*3);
	msg[0]=x; msg[1]=y ; msg[2] = z;

	}
}

void put_msg(int i ,int x, int y ){
  int* msg;
  msg = malloc(sizeof(int)*3);
  msg[0]=(unsigned)time(NULL);  msg[1]=x;  msg[2]=y;
  add_record(i,msg);
  free(msg);
}


