// mod


#include <stdlib.h>
#include <string.h>

typedef struct mt_record_struct{
  char* table;
  size_t w; // width
  int n;    // number of entries
  int c;    // current capacity 
  int max   // maxiumum entries 
} mt_record_struct;


mt_record_data* mtrs;

static int _N_COLS ;
static int _N_TABLES=0;
static int **_records;
static int *_n;
static int _max = 500;
static int *_capacity;
static char _is_init=0;
static double _fill_ratio = 0.8;

// init recorder;
int mt_recorder_init(size_t width, int capacity, int max){
  int ret = -1;
  if (_N_TABELS == 0){
    mtrs = malloc(sizeof(mt_record_struct));
    mtrs[0].table = malloc(width*capacity);
    ret = 0;
    _N_TABELS++;
  }
  else if (_N_TABLES > 0){
    mtrs = realloc(mtrs,sizeof(mt_record_struct)*(_N_TABLES+1));
    mtrs[_N_TABELS].table = malloc(width*capacity);
    ret = 0;
    _N_TABLES++;
  _records = malloc(sizeof(int*)*_N_TABLES);
  _n = malloc(sizeof(int)*_N_TABLES);
  _capacity = malloc(sizeof(int)*_N_TABLES);
  int i;
  for(i=0;i<_N_TABLES;i++){
    _records[i] = malloc(sizeof(int)*_N_COLS*capacity);
    _n[i]=0;
    _capacity[i]=capacity;
  }
}

int init_table(int index, size_t width, int capacity, int max){
  mtrs[ind

 }

void free_recorder(){
  int i;
  for (i=0;i<_N_TABLES;i++){
    free(_records[i]);
  } 
  free(_records);
  _is_init = 0;
}
int recorder_is_init(){
	return _is_init;
}

// returns number of records
int n(int table){
	return _n[table];
}

// adds record returns if succesful
int add_record(int table,int* vals){

	int ret = 0;
	if (check_capacity(table)){
		int i=0,*ptr;
		ptr = _records[table];
		ptr = ptr+(_n[table]*_N_COLS);
		memcpy(ptr,vals,_N_COLS*sizeof(int));
		_n[table]++;
		ret = 1;
	}

	return ret;
}


//returns pointer to records
int* records(int i ){
	return _records[i];
}

// checks capacity, increases by x2 if over fill ratio , returns 1 if there is room for at least one more record after,

int check_capacity(int i){
	int ret = 0;
	double x = (double)_n[i] / (double)_capacity[i];
	int remaining = _capacity[i] - _n[i];
	if (x > _fill_ratio){
	  ret = multiply_capacity(i,2);
	}
	else if ( x < _fill_ratio){
		ret = 1;
	}
	return ret;
}

// multiplies capacity to multiple x, or to max if max is smaller / returns 1 if succesful in increasing any amount
int multiply_capacity(int i, int x){
	int ret = 0;
	int newcap = _capacity[i] * x;
	if (newcap <= _max){
	  _records[i] = realloc(_records[i],sizeof(int)*newcap);
	  _capacity[i] = newcap;
	  ret = 1;
	}
	else if (newcap > _max && newcap > _n[i]){
	  _records[i] = realloc(_records[i],sizeof(int)*_max);
	  _capacity[i] = _max;
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
int clear_records(int i){
	int temp = _n[i];
	_n[i] = 0;
	return temp;
}
