/*
 * udp_adapter.c
 *
 *  Created on: Feb 25, 2016
 *      Author: matthew
 */



int udp_listen(char* ipaddr, char** ret_buff, size_t *ret_size);

int udp_send(char* ipaddr, char** send_buff, size_t *send_size);
