#ifndef MT_RECORDER_H
#define MT_RECORDER_H


// init recorder;
void init_recorder(int tables,int capacity);
void free_recorder();
int recorder_is_init();
int n(int table);
int add_record(int table,int* vals);
int* records(int i);
int check_capacity(int i);
int multiply_capacity(int i, int x);
int clear_records(int i);








#endif
