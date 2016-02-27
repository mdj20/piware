#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "mt_log.h"


int main(int argc , char** argv){

	int table1 = mt_recorder_init(sizeof(int)*5,50,500);

	int* msg;
	msg = malloc(sizeof(int)*5);
	int i , j ;
	for(i=0;i<100;i++){
		for(j=0;j<5;j++){
			msg[j] = i;
		}
		mt_add_record(table1,msg);
	}

	free(msg);

	printf("this\n");

	int* back;
	back = records(table1);

	for(i=0;i<100;i++){
		for(j=0;j<5;j++){
			printf("%d ",back[(5*i)+j]);
		}
		printf("\n");
	}

	printf("this");


	return 0;


}
