#ifndef LOC_AGREGATE_H
#define LOC_AGREGATE_H

// there should be a file that describes the ID format for now below will suffice


int add_home_member(char* id , char* dist);
int member_exists(char* id);
int update_member(char* id, char* val);
int get_member(char* id, char* val);
int add_guest(char* id , char* dist);
int update_guest(char* id, char* val);
int get_guest(char* id, char* val);

#endif


//int main(int argc, char** argv){};



