#include<stdio.h>
#include<stdlib.h>
#include"udp_adapter.h"
#include<string.h>


int d_port = 54321;

int main(int argc, char** argv){

	if(argc != 4  && argc != 3){
		printf("\nSYTAX: <(s)end/(r)ecv> xxx.xxx.xxx.xxx  \"Message (if sending)\"");
	}

	if(argv[1][0] == 's'){
		char *addr;
		char *msg;
		size_t msg_len = strlen(argv[3])+1;
		int add_len = strlen(argv[2]);
		msg=malloc(msg_len);
		strcpy(msg,argv[3]);
		addr = malloc(add_len);
		strcpy(msg,argv[3]);
		udp_send(addr,54321,&msg,&msg_len);
	}
	else if (argv[1][0] == 'r'){
		size_t size;
		size = (size_t) 512;
		char* msg;
		msg = malloc(size);
		udp_listen(d_port,&msg,size);
		printf("Received : \n%s",msg);
	}
	return 0;
}
