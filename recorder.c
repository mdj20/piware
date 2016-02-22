#include <stdlib.h>
#include <string.h>

static int _N_COLS = 3;
static int _N_TABLES=2;
static int *_records;
static int *_n;
static int _max = 500;
static int *_capacity = 50;
static char _is_init=0;
static double _fill_ratio = 0.8;

// init recorder;
void init_recorder(int capacity){
	_capacity = capacity;
	_records = malloc(sizeof(int)*_capacity*_N_COLS*_N_TABLES);
	_is_init = 1;
}
void free_recorder(){
	free(_records);
	_is_init = 0;
}
int recorder_is_init(){
	return _is_init;
}

// returns number of records
int n(){
	return _n;
}

// adds record returns if succesful
int add_record(int table,int* vals){

	int ret = 0;
	if (check_capacity(table)){
		int i=0,*ptr;
		ptr = _records;
		ptr = ptr+(_n*_N_COLS*(1+table));
		memcpy(ptr,vals,_N_COLS*sizeof(int));
		_n++;
		ret = 1;
	}

	return ret;
}

//returns pointer to records
int* records(){
	return _records;
}

// checks capacity, increases by x2 if over fill ratio , returns 1 if there is room for at least one more record after,

int check_capacity(){
	int ret = 0;
	double x = (double)_n / (double)_capacity;
	int remaining = _capacity - _n;
	if (x > _fill_ratio){
		ret = multiply_capacity(2);
	}
	else if ( x < _fill_ratio){
		ret = 1;
	}
	return ret;
}

// multiplies capacity to multiple x, or to max if max is smaller / returns 1 if succesful in increasing any amount
int multiply_capacity(int x){
	int ret = 0;
	int newcap = _capacity * x;
	if (newcap <= _max){
		_records = realloc(_records,sizeof(int)*newcap);
		_capacity = newcap;
		ret = 1;
	}
	else if (newcap > _max && newcap > _n){
		_records = realloc(_records,sizeof(int)*_max);
		_capacity = _max;
		ret = 1;
	}
	return ret;
}

 // clears records returns number cleared
int clear_records(){
	int temp = _n;
	_n = 0;
	return temp;
}
