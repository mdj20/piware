#ifndef RECORDER_H
#define RECORDER_H


// init recorder;
void init_recorder(int capacity);
void free_recorder();
int recorder_is_init();
int n();
int add_record(int* vals);
int* records();
int check_capacity();
int multiply_capacity(int x);
int clear_records();








#endif
