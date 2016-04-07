#include <stdlib.h>
#include "key_value.h" 

// there should be a file that describes the ID format for now below will suffice
size_t mem_id_size = 2;
size_t dist_id_size = 2;
int MAX_MEM = 15;

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

int update_member(char* id, char* val){
	put(members,id,val);
}

int get_member(char* id, char* val){
	//get(memberss,id,val);
}






//int main(int argc, char** argv){};



