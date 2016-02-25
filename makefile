all:
	gcc multi_piware.c recorder.c -o multi_piware.o -pthread


mtb_test :
	gcc mtb_test.c mt_buffer.c -o mtb_test.o -pthread
