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
		int add_len = strlen(argv[1]);
		int msg_len = strlen(argv[3]);
		msg=malloc(msg_len);
		strcpy(msg,argv[3]);
		addr = malloc(add_len);
		strcpy(msg,argv[1])
		udp_send(argv[2],msg,msg_len);
	}
	else if (argv[1] == 'r'){
		size_t *size;
		char* msg;
		int add_len = strlen(argv[1]);
		int msg_len = strlen(argv[3]);
		msg=malloc(msg_len);
		strcpy(msg,argv[3]);


		udp_listen();


	}

}
