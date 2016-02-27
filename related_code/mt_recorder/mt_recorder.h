#ifndef MT_RECORDER_H
#define MT_RECORDER_H



// init recorder;
int mt_recorder_init(size_t width, int capacity, int max);
static int init_table(int index, size_t width, int capacity, int max_capacity);
void free_recorder();
int n(int index);
int mt_add_record(int index,int* vals);
void* records(int index );
int check_capacity(int index);
int multiply_capacity(int index, int x);
int clear_records(int index);







#endif
