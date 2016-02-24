#include <sys/types.h>
#include <pthread.h>

// thread safe buffer modual
int _N_BUFFER = 0;

typedef struct _node {
  size_t size;
  node* next;
} node;

typedef struct _llist{
  node* head;
  node* tail;
  char init;
} llist;

typedef struct _mtb_struct {
  char* buff;
  pthread_mutex_t mutex;
  size_t b_size;  // buffer size
  int m_size;  // total isize of msges;
  int n_msg;   // number mesages
  llist list;
} mtb_struct;

mtb_struct* mtbs;
int mt_buffer_init(size_t size){
  if(_N_BUFFER==0){
    mtbs = malloc(sizeof(mtb_struct));
    mtbs[0].buff = malloc(sizeof(char)*size);
    mtbs[0].b_size = size;
    mtbs[0].llist.init = 0;
    pthread_mutex_init(&(mtbs[0].mutex),NULL)
  }
  else if(_N_BUFFER>0){
    mtbs = realloc(mtbs,(sizeof(mtb_struct)*(_N_BUFFER+1)));
    _N_BUFFER++;
    mtbs[_N_BUFFER-1].buff = malloc(sizeof(char)*size);
    mtbs[_N_BUFFER-1].b_size = size;
    mtbs[_N_BUFFER-1].list.init = 0;
    pthread_mutex_init(&(mtbs[_N_BUFFER-1].mutex),NULL)
  }
  return _N_BUFFER;
}

int put_msg(int buf_index, size_t size, void * addr){
  if(buff_index >= _N_BUFFER || buff_index < 0 ){
    return -1;
  }
  else {





  }
}
