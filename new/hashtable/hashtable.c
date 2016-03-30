#include <stdio.h>
#include <stdlib.h>
#include "uthash.h"

typedef struct device_h{
	int did;
	int dlocation;
	UT_hash_handle hh;
}device_h;

int local_id = 0;
char init = 0;
device_h *devices = NULL;  // NOTE: this is required for the uthash.h to function

int init_hash_table(int id){
	if (!init){
	local_id = id;
	init = 1;
	return 1;
	}
	else{
		return 0;
	}
}

int add_home_device(int id){
	int ret=0;
	if (init){
		device_h *d;
		HASH_FIND_INT(devices,&id,d);   //gets structure from hash table
		if(d==NULL){
			d = malloc(sizeof(device_h));
			d->did = id;
			d->dlocation = local_id;
			HASH_ADD_INT(devices,did,d);     // uses a macro to hash the structure;
			ret = 1;
		}
	}
	return ret;
}

int set_loaction(int id, int location){
	int ret=0;
	if (init){
		device_h *d;
		HASH_FIND_INT(devices,&id,d);
		if(d!=NULL){
			d->dlocation = local_id;
			ret = 1;
		}
	}
	return ret;
}

int get_location(int id){
	int ret = 0;
	if (init){
		device_h *d;
		HASH_FIND_INT(devices,&id,d);
		if (d!=NULL){
			ret = d->dlocation;
		}
	}
	return ret;
}

int remove_home_device(int id){
	int ret = 0;
	if (init){
		device_h *d;
		HASH_FIND_INT(devices,&id,d);
		if(d!=NULL){
			HASH_DEL(devices,d);
			free(d);
			ret =1;
		}
	}
	return ret;
}

int n_devices(){
	if(init)
		return HASH_COUNT(devices);
	else
		return -1;
}
