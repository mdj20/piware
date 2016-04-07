#include <stdlib.h>
#include "mt_buffer.h"
#include "key_value.h"

static int send_port = 4444;
static int recv_port = 5555;
static dest_port = 6666;
static size_t msg_size = 1024;


typedef struct thread_struct {
	int flow;
	int in_buffer;
	int out_buffer;
	int kv;
	char* ipaddr;
} thread_struct;

typedef struct debug_format {
	int task;
	int A;
	int B;
}debug_format;


int *loc_main_fcn(void *params){
	thread_struct *control = (thread_struct*)params; // get params
	for (;;){
		switch(control->flow){
			case 0: //work
				main_work(control->in_buffer,control->out_buffer,control->kv);
			break;
			case 1: // exit
				pthread_exit(NULL);
			break;
		}
	}
}


int main_work(int in , int out, int kv){
	debug_format* msg;
	size_t size = 0;
	int ready = -1;
	int * val;
	ready = mtb_dequeue(out,&msg,&size);
	if (ready){
		if(msg->task == 0){
			put(kv,&(msg->A),&(msg->B));
		}
		else if (msg->task == 1){
			val = malloc(sizeof(int));
			get(kv,&(msg->A),val);


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
				send_work(control->out_buffer,dest_port,send_port,control->ipaddr);
				sleep(10);
			break;
			case 1: // exit
				pthread_exit(NULL);
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
		udp_send(ipaddr,d_port,s_port,&send_buf,size);
		free(send_buf);
	}
	return msg_ready;
}

int *recv_fcn(void* params){
	thread_struct *control = (thread_struct*)params; // get params
	for (;;){
		switch(control->flow){
			case 0: //work
				recv_work(control->in_buffer,recv_port);
				sleep(10);
			break;
			case 1: // exit
				pthread_exit(NULL);
			break;
		}
	}
	return 0;
}

int recv_work(int in, int port){
	char* new_msg;
	size_t buf_size=0;
	size_t msg_size = 0;
	new_msg = malloc(msg_size);
	msg_size = udp_listen(recv_port,&new_msg,buf_size);
	if (msg_size > 0){
		mtb_enqueue(in,msg_size,new_msg);
	}
}

