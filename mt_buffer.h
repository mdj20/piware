#ifndef MT_BUFFER_H
#define MT_BUFFER_H

//ptypes
int mtb_num_msg(int buf_index);
int mt_buffer_init(size_t size);
int mtb_enqueue(int buf_index, size_t size, void *addr);
int peek(int index);
static int enqueue(int index, size_t size, void* addr);
static int first_msg(int index, size_t size, void *addr);
int mtb_dequeue(int index,void **addr, size_t *ret_size);



#endif
