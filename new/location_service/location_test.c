#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include "mt_buffer.h"
#include "key_value.h"
#include "ls_threads.h"
#include "loc_agregate.h"
#include "t_struct.h"

int main(int argc, char* argv[]){

	const char* ip = "123.123.123.123";

	int mtbin = mt_buffer_init(1024);
	int mtbout = mt_buffer_init(1024);

	int i = 0 ;
	for(i = 0 ; i < 10 ; i++){
		add_home_member(&i,&i);
	}

	thread_struct* tstruct;
	tstruct->flow = 0;
	tstruct->in_buffer = mtbin;
	tstruct->out_buffer= mtbout;
	tstruct->ipaddr = ip;

	pthread_t threads[3];

	pthread_create(&(threads[0]),NULL,loc_main_fcn,tstruct);
	pthread_create(&(threads[1]),NULL,sender_fcn,tstruct);
	pthread_create(&(threads[2]),NULL,recv_fcn,tstruct);

	tstruct->flow = 1;
	pthread_join(threads[0],NULL);
	pthread_join(threads[1],NULL);
	pthread_join(threads[2],NULL);

	return 0;

}
