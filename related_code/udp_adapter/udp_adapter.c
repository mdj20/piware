/*
 * udp_adapter.c
 *
 *  Created on: Feb 25, 2016
 *      Author: matthew
 */


#include<sys/types.h>
#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include"udp_socketbuilder.h"

u_short _default_port = 54321;
size_t _default_size = 512;


//int udp_listen_blocking();


int udp_listen(char* ipaddr, char** ret_buff, size_t *ret_size){

	int sock = get_socket();
	name_socket(sock,_default_port);



}



int udp_send(char* ipaddr, char** send_buff, size_t *send_size){



}
