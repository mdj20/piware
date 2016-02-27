// mod

#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct mt_record_struct{
  char* table;
  size_t w; // width
  int n;    // number of entries
  int c;    // current capacity 
  int max;  // maxiumum entries
  pthread_mutex_t mutex;
} mt_record_struct;


mt_record_struct* mtrs;
static int _N_TABLES=0;
/*static int _N_COLS ;

static int **_records;
static int *_n;
static int _max = 500;
static int *_capacity;
static char _is_init=0;
*/
static double _fill_ratio = 0.8;

//ptypes
static int init_table(int index, size_t width, int capacity, int max_capacity);
void free_recorder();
int n(int index);
int mt_add_record(int index,void* vals);
void* records(int index );
int check_capacity(int index);
int multiply_capacity(int index, int x);
int clear_records(int index);

// init recorder;

int mt_recorder_init(size_t width, int capacity, int max){
  int ret = -1;
  if (_N_TABLES == 0){
	  mtrs = malloc(sizeof(mt_record_struct));
	  if(mtrs != NULL )
		  ret = init_table(_N_TABLES,width,capacity,max);
	  if (ret > -1){
		  _N_TABLES++;
	  }
	  else{
		  printf("\nmt_recorder -> unable to allocate table\n");
		  free(mtrs);
	  }
  }
  else if (_N_TABLES > 0){
    mt_record_struct* temp;
	temp = realloc(mtrs,sizeof(mt_record_struct)*(_N_TABLES+1));
	if (temp == NULL){
		ret= -1;
	}
	else{
		mtrs=temp;
		ret = init_table(_N_TABLES,width,capacity,max);
		if(ret > -1){
			_N_TABLES++;
		}
		else{
			printf("\n Unable to allocate table\n");
		}
	}
  }
  return ret;
}

static int init_table(int index, size_t width, int capacity, int max_capacity){
	int ret = -1;
	mtrs[index].table = malloc(width*capacity);
	if (mtrs[index].table != NULL){
		mtrs[index].c = capacity;
		mtrs[index].max = max_capacity;
		mtrs[index].w = width;
		mtrs[index].n = 0;
		pthread_mutex_init(&(mtrs[index].mutex),NULL);
		ret = index;
	}
	return ret;
}

void free_recorder(){
  int i;
  for (i=0;i<_N_TABLES;i++){
    free(mtrs[i].table);
  } 
  _N_TABLES = 0;
}

// returns number of records
int n(int index){
	int ret = 0;
	pthread_mutex_lock(&(mtrs[index].mutex));
	ret = mtrs[index].n;
	pthread_mutex_unlock(&(mtrs[index].mutex));
	return ret;
}

// adds record returns if succesful
int mt_add_record(int index,void* vals){
	pthread_mutex_lock(&(mtrs[index].mutex));
	int ret = 0;
	if (check_capacity(index)){
		char * ptr;
		ptr = mtrs[index].table;
		ptr = ptr+(mtrs[index].n*mtrs[index].w);
		memcpy(ptr,vals,mtrs[index].w);
		mtrs[index].n++;
		ret = 1;
	}

	pthread_mutex_unlock(&(mtrs[index].mutex));
	return ret;
}


//returns pointer to records
void* records(int index ){
	return mtrs[index].table;
}

// checks capacity, increases by x2 if over fill ratio , returns 1 if there is room for at least one more record after,

int check_capacity(int index){
	int ret = 0;
	double x = (double)mtrs[index].n/(double)mtrs[index].c;
	int remaining = mtrs[index].c - mtrs[index].n;
	if (x >_fill_ratio){
	  ret = multiply_capacity(index,2);
	}
	else{
		ret = 1;
	}
	return ret;
}

// multiplies capacity to multiple x, or to max if max is smaller / returns 1 if succesful in increasing any amount
int multiply_capacity(int index, int x){
	int ret = 0;
	int newcap = mtrs[index].c * x;
	if (newcap <= mtrs[index].max){
		mtrs[index].table = realloc(mtrs[index].table,mtrs[index].w*newcap);
		mtrs[index].c = newcap;
	  ret = 1;
	}
	else if (newcap > mtrs[index].max && newcap > mtrs[index].n){
		mtrs[index].table = realloc(mtrs[index].table,mtrs[index].w*mtrs[index].max);
		mtrs[index].c = mtrs[index].max;
		ret = 1;
	}
	return ret;
}

/*
int trim_to_size(){

  _records[i]


}
*/

 // clears records returns number cleared
int clear_records(int index){

	pthread_mutex_lock(&(mtrs[index].mutex));
	int temp = mtrs[index].n;
	mtrs[index].n = 0;

	pthread_mutex_unlock(&(mtrs[index].mutex));
	return temp;
}
