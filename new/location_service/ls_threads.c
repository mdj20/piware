#include <stdlib.h>
#include "mt_buffer.h"
#include "udp_adapter.h"
#include "loc_agregate.h"
#include "t_struct.h"

static int send_port = 4444;
static int recv_port = 5555;
static dest_port = 6666;
static max_msg_size = 1024;


typedef struct debug_format {
	int task;
	int A;
	int B;
} debug_format ;

size_t msg_size = sizeof(debug_format);


int *loc_main_fcn(void *params){
	thread_struct *control = (thread_struct*)params; // get params
	for (;;){
		switch(control->flow){
			case 0: //work
				main_work(control->in_buffer,control->out_buffer);
				break;
			case 1: // exit
				pthread_exit(NULL);
				break;
			case 2: // debug
				main_debug(control->in_buffer,control->out_buffer);
			break;
		}
	}
}


int main_work(int in , int out){
	debug_format* msg;
	size_t size = 0;
	int ready = -1;
	int * val;
	ready = mtb_dequeue(in,&msg,&size);
	if (ready == 1){
		if(msg->task == 0){
			update_member(&(msg->A),&(msg->B));
		}
		else if (msg->task == 1){
			val = malloc(sizeof(int));
			get_member(&(msg->A),val);
			debug_format * new_msg;
			new_msg = malloc(sizeof(debug_format));
			new_msg->task = 0;
			new_msg->A = msg->A;
			new_msg->B = msg->B;
			mtb_enqueue(out,sizeof(debug_format),new_msg);
		}
		free(msg);
	}

}

int main_debug(int in , int out){

	debug_format* msg;
	size_t size = 0;
	int ready = -1;
	int * val;
	ready = mtb_dequeue(in,&msg,&size);
	if (ready==1){
		if(msg->task == 0){
			update_member(&(msg->A),&(msg->B));
			printf("Update:\nLeader: %d\nLocation: %d\n\n",msg->A,msg->B);
		}
		else if (msg->task == 1){
			printf("in 1\n");
			val = malloc(sizeof(int));
			get_member(&(msg->A),val);
			debug_format * new_msg;
			new_msg = malloc(sizeof(debug_format));
			new_msg->task = 1;
			new_msg->A = msg->A;
			new_msg->B = msg->B;
			mtb_enqueue(out,sizeof(debug_format),new_msg);
		}
		free(msg);
	}
}


// debug functions below
int *sender_fcn(void* params){
	thread_struct *control = (thread_struct*)params; // get params
	for (;;){
		switch(control->flow){
			case 0: //work
				//send_work(control->out_buffer,dest_port,send_port,control->ipaddr);
				printf("Hello \n");
				sleep(1);
			break;
			case 1: // exit
				pthread_exit(NULL);
			break;
			case 2: // loc_debug
				send_debug(control->out_buffer);
			break;
		}
	}
}

int send_work(int out, int d_port, int s_port, char* ipaddr){
	char* send_buf;
	size_t size = 0;
	int msg_ready = -1;
	msg_ready = mtb_dequeue(out,&send_buf,&size);
	if (msg_ready>-1){
		udp_send(ipaddr,d_port,s_port,&send_buf,&size);
		free(send_buf);
	}
	return msg_ready;

}

int send_debug(int out){
	debug_format* df;
	size_t size = 0;
	int msg_ready = -1;
	msg_ready = mtb_dequeue(out,&df,&size);
	if(msg_ready > -1){
		if(size == sizeof(debug_format)){
			printf("Output:\nTask: %d\nLeader: %d\nLocation: %d\n\n",df->task,df->A,df->B);
		}
		else{
			printf("Not debug format....\n");
		}
		free(df);
	}
	return size;
}

int *recv_fcn(void* params){
	thread_struct *control = (thread_struct*)params; // get params
	for (;;){
		switch(control->flow){
			case 0: //work
				//recv_work(control->in_buffer,recv_port);
				printf("hello R\n");
				sleep(1);
			break;
			case 1: // exit
				pthread_exit(NULL);
			break;
			case 2: // loc_debug
				recv_debug(control->in_buffer);
				sleep(1);
			break;
		}
	}
	return 0;
}

int recv_work(int in, int port){
	char* new_msg;
	size_t buf_size=0;
	size_t msg_size = 0;
	new_msg = malloc(max_msg_size);
	msg_size = udp_listen(recv_port,&new_msg,buf_size);
	if (msg_size > 0){
		mtb_enqueue(in,msg_size,new_msg);
	}
}

// creates random meassage format;
int recv_debug(int in){
	size_t dfsize = sizeof(debug_format);
	int a = 0, b = 0;
	a = rand()%10;
	b = rand()%10;
	debug_format* df;
	df = malloc(sizeof(debug_format));
	df->task = rand()%2;
	df->A = a;
	df->B = b;
	mtb_enqueue(in,dfsize,df);
	free(df);
}
