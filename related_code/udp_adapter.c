/*
 * udp_adapter.c
 *
 *  Created on: Feb 25, 2016
 *      Author: matthew
 */

u_short _default_port = 54321;
size_t _default_size = 512;

#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>



int udp_listen(char* ipaddr, char** ret_buff, size_t *ret_size){

	//allocate and 0 buffer
	 ret_buff = malloc(_default_size);
	 memset(ret_buff,0,_default_size);

	 // create and name socket
	 int sock;
	 struct sockaddr_in name;
	 sock = socket(AF_INET,SOCK_DGRAM,0);
	 if(sock < 0 ){
		printf("\nCan't create socket\n");
	 }

	 // name socket
	 name.sin_family = AF_INET;
	 name.sin_port = _default_port = htons(_default_port);
	 inet_aton(*ipaddr,&name.sin_addr.s_addr);

	 // bind
	 bind(sock,(struct sockaddr*) &name,sizeof(name));

	 //rec
	 *ret_size = recvfrom(sock,ret_buff,_default_size,0,&name,sizeof(name));

	 close(sock);

}

int udp_send(char* ipaddr, char** send_buff, size_t *send_size){

	struct hostent *hp;
	struct sockaddr_in servaddr;
	//allocate and 0 buffer

	 // create and name socket
	 int sock;
	 struct sockaddr_in serv_name;
	 sock = socket(AF_INET,SOCK_DGRAM,0);
	 if(sock < 0 ){
		printf("\nCan't create socket\n");
	 }

	 // name socket
	 serv_name.sin_family = AF_INET;
	 serv_name.sin_port = _default_port = htons(_default_port);
	 inet_aton(*ipaddr,&serv_name.sin_addr.s_addr);

	 // bind
	 bind(sock,(struct sockaddr*) &serv_name,sizeof(serv_name));

	 //rec
	 sendto(sock,send_buff,_default_size,0,&serv_name,sizeof(serv_name));

	 close(sock);

}
