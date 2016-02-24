#include <sys/types.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// thread safe buffer modual
int _N_BUFFER = 0;

typedef struct node node;

struct node {
  size_t node_size;
  node* next;
};

typedef struct llist{
  node* head;
  node* tail;
  char init;
} llist;

typedef struct mtb_struct {
  char* buff;
  pthread_mutex_t mutex;
  size_t b_size;  // buffer size
  int m_size;  // total isize of msges;
  int n_msg;   // number mesages
  llist list;
} mtb_struct;

//ptypes
int mtb_num_msg(int buf_index);
int mt_buffer_init(size_t size);
int mtb_enqueue(int buf_index, size_t size, void *addr);
int mtb_dequeue(int index,void **addr);
static int enqueue(int index, size_t size, void* addr);
static int first_msg(int index, size_t size, void *addr);

int peek(int index);
mtb_struct* mtbs;

int mt_buffer_init(size_t size){
  if(_N_BUFFER==0){
    mtbs = malloc(sizeof(mtb_struct));
    mtbs[0].buff = malloc(sizeof(char)*size);
    mtbs[0].b_size = size;
    mtbs[0].list.init = 0;
    _N_BUFFER++;
    pthread_mutex_init(&(mtbs[0].mutex),NULL);
  }
  else if(_N_BUFFER>0){
    mtbs = realloc(mtbs,(sizeof(mtb_struct)*(_N_BUFFER+1)));
    _N_BUFFER++;
    mtbs[_N_BUFFER-1].buff = malloc(sizeof(char)*size);
    mtbs[_N_BUFFER-1].b_size = size;
    mtbs[_N_BUFFER-1].list.init = 0;
    pthread_mutex_init(&(mtbs[_N_BUFFER-1].mutex),NULL);
  }
  return (_N_BUFFER-1);
}

//  
int mtb_enqueue(int index, size_t size, void *addr){
  int ret = -1;
  if(index >= _N_BUFFER || index < 0 ){
    ret =  -1;
    //    printf("in %d %d %d\n",ret,index,_N_BUFFER);
  }
  else{
    pthread_mutex_lock(&(mtbs[index].mutex));
    if(mtbs[index].m_size+size <= mtbs[index].b_size){
      ret = enqueue(index,size,addr); 
    }
    pthread_mutex_unlock(&(mtbs[index].mutex));
    // printf("in2 %d\n",ret);
  }
  return ret;
}
size_t mtb_dequeue(int index,void **addr){
  int ret = -1;
  if(index >= _N_BUFFER || index < 0 ){
    ret =  -1;
    //    printf("in %d %d %d\n",ret,index,_N_BUFFER);
  }
  else{
    pthread_mutex_lock(&(mtbs[index].mutex));
    int pop_size = pop_node(index);
    if( pop_size > 0 ){
      char* msg;
      msg = malloc(pop_size);
      memcpy(msg,mtbs[index].buff,pop_size);
      *addr = msg; // copy msg pointer value to ret addr
    }
    ret = pop_size;
    pthread_mutex_unlock(&(mtbs[index].mutex));
  }
  return ret;
}

int peek(int index){
 int ret = -1;
  if(index >= _N_BUFFER || index < 0 ){
    ret =  -1;
    //    printf("in %d %d %d\n",ret,index,_N_BUFFER);
  }
  else{
    pthread_mutex_lock(&(mtbs[index].mutex));
    ret = mtbs[index].list.head->node_size;
    pthread_mutex_unlock(&(mtbs[index].mutex));
  }
  return ret;
}

static int enqueue(int index, size_t size, void* addr){
  int ret = -1;
  if (mtbs[index].n_msg == 0){
    ret = first_msg(index,size,addr);
  }
  else{
    // append to linked list
    node *last = mtbs[index].list.tail;
    node *temp;
    temp = malloc(sizeof(node));
    last->next = temp;

    // copy msg
    char *ptr;
    ptr = mtbs[index].buff;
    ptr += mtbs[index].m_size;
    memcpy(ptr,addr,size);
    
    // increment nuber msgs and total size;
    mtbs[index].m_size += size;
    mtbs[index].n_msg++;
    ret = mtbs[index].n_msg;
  }
  return ret;
}

// returns size of first msg, will pop the fhead node off of the linked list and free memory if applicable. NOTE: index must be valid / if there is no msg will return 0 but not remove any node;
static size_t pop_node(int index){  
  size_t ret = 0;
  node* pop;
  if(mtbs[index].n_msg > 0 ){
    pop = mtbs[index].list->head;
    
    if (mtbs[index].n_msg > 1){
      mtbs[index].list->head = pop->next;
    }
    
    mtbs[index].n_msg--;
    ret = pop->node_size;
    free(pop);
  }
  return ret;
}

static int first_msg(int index, size_t size, void *addr){
  memcpy(mtbs[index].buff,addr,size);
  mtbs[index].n_msg = 1;
  mtbs[index].m_size = size;
  node * temp;
  temp = malloc(sizeof(node));
  temp->node_size = size;
  mtbs[index].list.head = temp;
  mtbs[index].list.tail = temp;
  mtbs[index].list.init = 1;
  return 1;
}

int mtb_num_msg(int index){
  int ret = -1;
  if(index >= _N_BUFFER || index < 0 ){
    ret = -1;
    printf("I %d\n",ret);
  }
  else{
    ret = mtbs[index].n_msg;
    printf("I %d\n",ret);
  }
  return ret;
}
