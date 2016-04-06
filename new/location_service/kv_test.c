#include <stdio.h>
#include "key_value.h"
#include <stdlib.h>




int main(int argc, char** argv){

	int id = create_table(sizeof(int),sizeof(int),10);
	printf("id %d\n",id);

	int intkeys[10];
	int intvals[10];
	int intret[10];

	int i =0;
	for(i = 0 ; i<10 ; i++){
		intkeys[i] = i;
		intvals[i] = i*10;
		put(id,&(intkeys[i]),&(intvals[i]));
	}

	for(i = 0 ; i<10 ; i++){
		get(id,&(intkeys[i]),&(intret[i]));
		printf("%d %d\n",intkeys[i],intret[i]);
	}



	return 0;
}
