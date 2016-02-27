/*
 * udp_adapter.c
 *
 *  Created on: Feb 25, 2016
 *      Author: matthew
 */
#ifndef UDP_ADAPTER_H
#define UDP_ADAPTER_H


int udp_listen(char* ipaddr, char** ret_buff, size_t *ret_size);
int udp_send(char* ipaddr, char** send_buff, size_t *send_size);



#endif
