// thread safe buffer modual
int _N_BUFFER = 0;

typedef struct _node {
  int size;
  node* next;
} node;

typedef struct _llist{
  node* head;
  node* tail;
} llist;

typedef struct _mtb_struct {
  pthread_mutex_t mutex;
  int b_size;  // buffer size
  int m_size;  // total isize of msges;
  int n_msg;   // number mesages
  llist list;
} mtb_struct;

mtb_struct* mtbs;
int mt_buffer_init(int size){
  if(_N_BUFFER==0){
    mtbs = malloc(sizeof(mtb_struct));
    mtbs[0].b_size = size;
    pthread_mutex_init(&(mtbs[0].mutex),NULL)
  }
  else if(_N_BUFFER>0){
    mtbs = realloc(mtbs,(sizeof(mtb_struct)*(_N_BUFFER+1)));
    _N_BUFFER++;
    mtbs[_N_BUFFER-1].b_size = size;
    pthread_mutex_init(&(mtbs[_N_BUFFER-1].mutex),NULL)
  }
  return _N_BUFFER;
}

