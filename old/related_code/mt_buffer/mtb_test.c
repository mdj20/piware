#include <stdio.h>
#include <stdlib.h>
#include "mt_buffer.h"
#include <string.h>
// a driver 


int main(int argc, char** argv){

  int index = mt_buffer_init(1024);
  printf("\n");

  printf("index: %d\n", index);

  int* msg,i,j;
  msg =malloc(sizeof(int)*10);
  memcpy(msg,"0",sizeof(int));
  for(j=0;j<10;j++){
    for (i=0;i<10;i++){
      msg[i]=i+j;
      printf("%d ",msg[i]);
    }
    printf("\nadded NUM %d to buffer \n",mtb_enqueue(index,sizeof(int)*10,msg));
  }

/*
  int* buff = mtb_get_buffer(index);
  for(i=0;i <99 ; i++){
	  printf("\n%d",buff[i]);
  }
*/

  void* msg_back;
  size_t ret_size;
  int k = 0 ;
  for (k=0;k < 10 ;k++){
    mtb_dequeue(index,&msg_back,&ret_size);
    int* ptr_back;
    ptr_back = msg_back;
    j = (int)ret_size/(sizeof(int));
    for(i=0;i<j;i++){
      printf("Ret %d:\n",ptr_back[i]);
    }
    printf("n_msg %d\n",mtb_num_msg(index));
    free(msg_back);
  }
  
  printf("\n\nMade it \n\n");
  
  //msg_back = realloc(msg_back,0);
  
  //printf("buffers: %d",mtb_num_msg(index));
  //printf("buffers: %d",(int)peek(index));
  return 0;
}
