/*
 * udp_adapter.c
 *
 *  Created on: Feb 25, 2016
 *      Author: matthew
 */

u_short _default_port = 54321;


#include<stdlib.h>
#include<sys/socket.h>



int listen(char* ipaddr){

	 int sock;
	 struct sockaddr_in name;

	 sock = socket(AF_INET,SOCK_DGRAM,0);
	 if(sock < 0 ){
		printf("\nCan't create socket\n");
	 }

	 name.sin_family = AF_INET;
	 name.port = _default_port = htons(54321);
	 name.sin_addr.s_addr =



}
