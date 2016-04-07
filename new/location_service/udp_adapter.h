/*
 * udp_adapter.c
 *
 *  Created on: Feb 25, 2016
 *      Author: matthew
 */
#ifndef UDP_ADAPTER_H
#define UDP_ADAPTER_H


int udp_listen_from(char* ipaddr, char** ret_buff, size_t *ret_size);
int udp_listen(int port, char** ret_buff, size_t size);
int udp_send(char* ipaddr,int port,int dest_port, char** send_buff, size_t *send_size);




#endif
