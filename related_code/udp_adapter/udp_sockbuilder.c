/*
 *
	Module will build and keep track of socket information open close etc
	will be build to be thread safe.

	NOTE: I don't know if a the socket tracking ability will be needed at this point.
	I may suffice to just chave each thread just create it's own socket when needed.

	for now it will just


*/

#include <sys/socket.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <netinet/ip.h>
#include <fcntl.h>


typedef struct sock_struct {
  // maximum
	int sock;
	int owned;
	pthread_t owner;
	int named;
} sock_struct;

//socketbuilder struct
int n_sock;
int max_sock;
sock_struct **sbs;
pthread_mutex_t *mutex;


// initalizes socket tracker may not need
int init_socket_tacker(int max_sockets){
	sbs = malloc(sizeof(sock_struct*)*max_sockets); //
	pthread_mutex_init(mutex,NULL);
	max_sock = 0;
	n_sock = 0;
	return 0;
}

// creates and returns non tracked socket.
int get_socket(){
	int ret = -1;
	ret   = socket(AF_INET,SOCK_DGRAM,0);
	return ret;
}

// returns socket to thread that cannot be renamed or accessed by other threads, until it is released.
int get_tracked_socket(){
	int ret = -1;


	return ret;
}


// this will
static int make_tracked_socket(){
	int ret = -1;
	pthread_mutex_lock(mutex);
	if (n_sock < max_sock){
		ret   = socket(AF_INET,SOCK_DGRAM,0);
	}
	if (ret != -1){
		sbs[n_sock]= malloc(sizeof(sock_struct));
		sbs[n_sock]->owned = 0;
		sbs[n_sock]->owner = 0;
		sbs[n_sock]->named = 0;
		sbs[n_sock]->sock = ret;
		n_sock++;	 // Increment number of sockets last for indexing continuity.
	}
	pthread_mutex_unlock(mutex);
	return ret;
}

// releases socket from exclusivity
int release_socket(int sock){
	return 0;
}

// fo now this will just call close
int close_socket(int sock){
	return close(sock);
}

// sets socket to blocking recv
int set_s_block(int sock){
	int flags = fcntl(sock,F_GETFL,0);
	return fcntl(sock,F_SETFL, flags & (~O_NONBLOCK));
}

// sets socket to non-blocking recv
int set_s_nonblock(int sock){
	int flags = fcntl(sock,F_GETFL,0);
	return fcntl(sock,F_SETFL, flags | O_NONBLOCK );
}

// names port to socket, returns value of bind.
int name_socket(int sock, int port){
	struct sockaddr_in name;
	name.sin_family = AF_INET;
	name.sin_port = htons(port);
	name.sin_addr.s_addr = htonl(INADDR_ANY);

	return bind(sock,(struct sockaddr*)&name,sizeof(struct sockaddr_in));
}













