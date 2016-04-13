#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

typedef int table_t;


// ptypes
int new_id();
int table_index(int sid);
int key_index(int tindex, char* k);
int put(int id, char* k , char* v);
int get_pointer(int id, char* k, char* v);

static int n = 0;

typedef struct kv {
	int id;
	int size;
	int n_pairs;
	size_t k_size;
	size_t v_size;
	char* keys;
	char* vals;
} kv ;

static kv *tables;

int create_table(size_t k, size_t v, int length){
	if (n==0){
		tables = malloc(sizeof(kv));
		tables[n].id = new_id();
		tables[n].k_size = k;
		tables[n].v_size = v;
		tables[n].n_pairs = 0;
		tables[n].size = length;
	}
	else{
		tables = realloc(tables,(sizeof(kv)*n)+1);
		tables[n].id = new_id();
		tables[n].k_size = k;
		tables[n].v_size = v;
		tables[n].n_pairs = 0;
		tables[n].size = length;
	}
	tables[n].keys = malloc(sizeof(k)*length);
	tables[n].vals = malloc(sizeof(v)*length);
	n++;
	return tables[n-1].id;
}

int put(int id, char* k , char* v){
	int ret = -1;
	int tindex = table_index(id);
	if(tindex >= 0 ){
		size_t ks = tables[tindex].k_size; // key size
		size_t vs = tables[tindex].v_size; // val size
		int kindex = key_index(tindex,k);
		if(kindex >= 0){
			memcpy(&(tables[tindex].vals[kindex*vs]),v,vs);
			ret = kindex;
		}
		else if (tables[tindex].n_pairs < tables[tindex].size ){
			memcpy(&(tables[tindex].keys[tables[tindex].n_pairs*ks]),k,ks);
			memcpy(&(tables[tindex].vals[tables[tindex].n_pairs*vs]),v,vs);
			int y = 0;
			int x = 0;
			memcpy(&x,&(tables[tindex].keys[tables[tindex].n_pairs*ks]),ks);
			memcpy(&y,&(tables[tindex].vals[tables[tindex].n_pairs*vs]),vs);
			ret = tables[tindex].n_pairs;
			tables[tindex].n_pairs++;

		}
		else{
			// increase size of table but not implimented now....
		}
	}
	return ret;
}

int get_pointer(int id, char* k, char* v){
	int ret = -1;
		int tindex = table_index(id);
		if(tindex >= 0 ){
			int kindex = key_index(tindex,k);
			size_t vs = tables[tindex].v_size;
			if(kindex >= 0){
				v = (tables[tindex].vals[kindex*vs]);
				ret = kindex;
			}
		}
	return ret;
}

int get(int id, char* k, char* v){
	int ret = -1;
		int tindex = table_index(id);
		if(tindex >= 0 ){
			int kindex = key_index(tindex,k);
			size_t vs = tables[tindex].v_size;
			if(kindex >= 0){
				memcpy(v,&(tables[tindex].vals[kindex*vs]),vs);
				ret = kindex;
			}
		}
	return ret;
}

int key_exists(int id,char* k){
	int ret = -1;
		int tindex = table_index(id);
		if(tindex >= 0 ){
			int kindex = key_index(tindex,k);
			if(kindex >= 0){
				ret = kindex;
			}
		}
	return ret;
}


int key_index(int tindex, char* k){
	int i = 0 ,ret = -1;
	size_t ks = tables[tindex].k_size; // size of key
	for (i = 0 ; i<tables[tindex].n_pairs; i++ ){
		int val = memcmp(k,&(tables[tindex].keys[i*ks]),ks);
		if(val==0){
			ret = i;
			i = tables[tindex].size;
		}
	}
	return ret;
}

int table_index(int sid){
	int i = 0, ret=-1;
	for (i=0;i<n;i++){
		if(tables[i].id == sid){
			ret = i;
			i=n;
		}
	}
	return ret;
}

int new_id(){
	srand(time(NULL));
	int ret = 0;
	int i = 0;
	int b = 0;
	do {
		ret = rand();
		for(i = 0 ; i < n ; i++){
			if(tables[i].id == ret){
				b = 1;
			}
		}
	} while (b);
	return ret;
}
