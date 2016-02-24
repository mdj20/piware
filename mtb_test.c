#include <stdio.h>
#include <stdlib.h>
#include "mt_buffer.h"
#include <string.h>

int main(int argc, char** argv){

  int index = mt_buffer_init(1024);
  printf("\n");

  printf("index: %d\n", index);

  int* msg,i,j;
  msg =malloc(sizeof(int)*10);
  memcpy(msg,"0",sizeof(int));
  for(j=1;j<10;j++){
    for (i=0;i<10;i++){
      msg[i]+=1;
    }
    printf("NUM %d\n",mtb_enqueue(index,sizeof(int)*10,msg));
  }


  printf("buffers: %d",mtb_num_msg(index));
  printf("buffers: %d",peek(index));
}
