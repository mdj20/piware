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


struct sockaddr_in udp_listen_from(char* ipaddr,int port, char** ret_buff,size_t buff_len ,size_t *ret_size){
	struct sockaddr_in remote;
	memset(&remote,0,sizeof(struct sockaddr_in));
	socklen_t remote_len;
	remote_len = sizeof(struct sockaddr_in);
	int sock = get_socket();
	if (sock > -1 && name_socket(sock,port) == 0){
		*ret_size  = recvfrom(sock,*ret_buff,buff_len,0,&remote,&remote_len);
	}
	close_socket(sock);
	return remote;
}

int udp_listen(int port, char** ret_buff, size_t size){
	int ret =-1;
	int sock = get_socket();
	if (sock > -1 && name_socket(sock,port) == 0){
		ret = recv(sock,*ret_buff,size,0);
	}
	close_socket(sock);
	return ret;
}

int udp_send(char* ipaddr, int port, char** send_buff, size_t *send_size){
	int ret = -1;
	struct sockaddr_in dest_addr;
	set_addr(&dest_addr,ipaddr);
	int sock = get_socket();
	if (sock > -1 && name_socket(sock,port) == 0){
		ret = sendto(sock,send_buff,*send_size,0,&dest_addr,sizeof(struct sockaddr_in));
	}
	return ret;
}
