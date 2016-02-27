#ifndef UDP_SOCKETBUILDER_H
#define UDP_SOCKETBUILDER_H




int init_socket_tacker(int max_sockets);
int get_socket();
int get_tracked_socket();
static int make_tracked_socket();
int release_socket(int sock);
int close_socket(int sock);
int set_s_block(int sock);
int set_s_nonblock(int sock);
int name_socket(int sock, int port);




#endif







