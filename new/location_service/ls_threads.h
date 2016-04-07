#ifndef LS_THREADS_H
#define LS_THREADS_H


int *loc_main_fcn(void *params);
int main_work(int in , int out);
int *sender_fcn(void* params);
int send_work(int out, int d_port, int s_port, char* ipaddr);
int *recv_fcn(void* params);
int recv_work(int in, int port);

#endif
