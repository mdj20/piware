#ifndef KEY_VALUE_H
#define KEY_VALUE_H

int create_table(size_t k, size_t v, int length);
int new_id();
int table_index(int sid);
int key_index(int tindex, char* k);
int put(int id, char* k , char* v);
int get_pointer(int id, char* k, char* v);
int get(int id, char* k, char* v);
int key_exists(int id,char* k);

#endif
