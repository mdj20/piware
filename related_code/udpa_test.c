#include<stdio.h>
#include<stdlib.h>
#include"udp_adapter.h"
#include<string.h>

int main(int argc, char** argv){

	if(argc != 4  && argc != 3){
		printf("\nSYTAX: <(s)end/(r)ecv> xxx.xxx.xxx.xxx  \"Message (if sending)\"");
	}

	if(argv[1] == 's'){
		char *addr;
		char *msg;
		size_t msg_len = strlen(argv[3]);
		int add_len = strlen(argv[2]);
		msg=malloc(msg_len);
		strcpy(msg,argv[3]);
		addr = malloc(add_len);
		strcpy(msg,argv[3]);
		udp_send(addr,&msg,&msg_len);
	}
	else if (argv[1] == 'r'){
		size_t *size;
		*size = 0;
		char* addr;
		char* msg;
		int add_len = strlen(argv[2]);
		addr = malloc(add_len);


		udp_listen(addr,&msg,size);


	}

}
