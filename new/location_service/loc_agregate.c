#include <stdlib.h>
#include "key_value.h" 

// there should be a file that describes the ID format for now below will suffice
size_t mem_id_size = 2;
size_t dist_id_size = 2;
int MAX_MEM = 15;
int MAX_TEMP = 15;

int members=-1;
int mem_init = 0;

int guest = -1;
int guest_init = 0;

int add_home_member(char* id , char* dist){
	int ret = -1;
	if (!mem_init){
		members = create_table(mem_id_size,dist_id_size,MAX_MEM);
	}
	ret = put(members,id,dist);
	return ret;
}

int member_exists(char* id){
	return key_exists(members, id );
}

int update_member(char* id, char* val){
	return put( members,id,val );
}

int get_member(char* id, char* val){
	return get( members,id,val );
}

int add_guest(char* id , char* dist){
	int ret = -1;
	if ( !guest_init ){
		guest = create_table(mem_id_size,dist_id_size,MAX_MEM);
	}
	ret = put(guest,id,dist);
	return ret;
}

int update_guest(char* id, char* val){
	int ret = -1;
	ret = put(guest,id,val);
	return ret;
}

int get_guest(char* id, char* val){
	int ret = -1;
	ret = get(guest,id,val);
	return ret;
}




