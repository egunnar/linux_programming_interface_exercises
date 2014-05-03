/*
What is the effect of the following statements? fflush(fp); fsync(fileno(fp)); 

Note, I ran with strace to prove my assertions below.
*/

#include <stdio.h>

void  fflush_example(){
	FILE* fh = fopen("tmp.txt", "w");
	fprintf(fh, "x"); // becomes write(3, "x", 1)

	// To answer question 1, fflush will force a system call to write 
	// unlike the two fprintf calls below that will be condensed into
	// one write call
	fflush(fh);

	fprintf(fh, "x"); // with the statement below becomes write(3, "xx", 2) 
	fprintf(fh, "x");

	fclose(fh);
}

void fsync_example(){

	FILE* fh = fopen("tmp.txt", "w");

	int file_descriptor = fileno(fh);

	// simliar to fflush 
	// statements below becomes write(3, "xx", 2)
	// the difference is it also flushes the buffer to the disk device.
	// because of this fsync is blocking
	fprintf(fh, "x");  
	fprintf(fh, "x");

	fsync(file_descriptor);

	fclose(fh);
}

void usage(){
	fprintf(stderr, "ERROR: run with one argument, either fflush or fsync\n");
}

int main(int argc, char * argv[]){
	if (strcmp(argv[1], "fflush") == 0){
		fflush_example();
	}else if (strcmp(argv[1], "fsync") == 0){
		fsync_example();
	}else{
		usage();
	}
}

