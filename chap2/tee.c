#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int BUFFER_SIZE = 1000;


void exitError(char * additional_message){
	fprintf(stderr, additional_message);
	fprintf(stderr, strerror(errno));
	exit(1);
}

void usage(){
	fprintf(stderr, "Usage: tee [-a] [FILE]\n");
	exit(1);
}

int main(int argc, char *argv[]){

	bool do_append = false;
	int c;	
	char * file_name = "";
	char *buff = malloc(BUFFER_SIZE);
	int bytes_read;
	if (buff == NULL){
		fprintf(stderr, "malloc failed");
		exit(1);
	}

	while ((c = getopt(argc, argv, "a")) != -1 ){
		if (c == 'a'){
			do_append = true;
		}else if (c == '?'){
			exit(1);
		}
	}

	if (do_append && (argc != 3))
		usage();
	if ((!do_append) && (argc != 2))
		usage();

	file_name = argv[optind];

	int open_flag = O_WRONLY | O_CREAT;
	if (do_append){
		open_flag |= O_APPEND;
	}
	// rw-rw-rw- 
	mode_t permission_mode = S_IROTH | S_IWOTH | S_IRUSR | S_IWUSR | 
		S_IRGRP | S_IWGRP;

	int fd_tee_file = open(file_name, open_flag, permission_mode);
	
	while(1){	
		bytes_read = read(STDIN_FILENO, buff, BUFFER_SIZE);
		if (bytes_read == -1){
		}
		fprintf(stderr, "bytes read:%d\n", bytes_read);
		if (bytes_read <= 0){
			break;
		}
		write(STDOUT_FILENO, buff, bytes_read);
		write(fd_tee_file, buff, bytes_read);
	}	
	close(fd_tee_file);
	return 0;
}
