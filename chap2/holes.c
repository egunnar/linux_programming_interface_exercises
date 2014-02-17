#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int BUFFER_SIZE = 1000;

void exit_error(char * additional_message){
	fprintf(stderr, additional_message);
	fprintf(stderr, strerror(errno));
	exit(1);
}

void usage(){
	fprintf(stderr, "cp <source file> <target file>\n");
}

int main(int argc, char * argv[]){

	int ret_val;

	if (argc != 3){
		usage();
		exit(1);
	}

	// create buffer and writing for reading later
	char *buff = malloc(BUFFER_SIZE);
	int bytes_read;
	if (buff == NULL){
		fprintf(stderr, "malloc failed");
		exit(1);
	}

	// open out file
	mode_t permission_mode = S_IROTH | S_IWOTH | S_IRUSR | S_IWUSR | 
		S_IRGRP | S_IWGRP;
	int fd_out_file = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, permission_mode);
	if (fd_out_file == -1){
		exit_error("openning target file failed");
	}

	// open in file
	int fd_in_file = open(argv[1], O_RDONLY);
	if (fd_in_file == -1){
		exit_error("openning source file failed");
	}

	while ((bytes_read = read(fd_in_file, buff, BUFFER_SIZE)) > 0){
		ret_val = write(fd_out_file, buff, bytes_read);
		if (ret_val == -1){
			exit_error("writing to stdout failed");
		}
	}
	if (bytes_read == -1){
		exit_error("reading from stdin failed");
	}

	return 0;
}

