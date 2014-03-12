#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>

/* usage <program> filename num-bytes [x]
should open filename (creating if necessary) and append num-bytes to write a
byte at a time. the default is to open the file with the O_APPEND flag, but if
the third command line arg is present then O_APPEND shouldn't be used (instead
perform a lseek(fd, 0, SEEK_END) before each call to write()). */

void exit_error(char * additional_message){
	fprintf(stderr, additional_message);
	fprintf(stderr, strerror(errno));
	exit(1);
}

int main(int argc, char * argv[]){
	if ((argc != 4) && (argc != 3)){
		usage();
	}
	char * filename = argv[1];

	int do_append = 0;
	if (argc == 4){
		do_append = 1;
	}

	int number_of_bytes = atoi(argv[2]);

	int open_flag = O_WRONLY | O_CREAT;
	if (do_append){
		open_flag |= O_APPEND;
	}

	// rw-rw-rw- 
	mode_t permission_mode = S_IROTH | S_IWOTH | S_IRUSR | S_IWUSR | 
		S_IRGRP | S_IWGRP;

	int fd = open(filename, open_flag, permission_mode);
	int ret_val;
	int i = 0;
	for (i = 0; i <= number_of_bytes; ++i){
		if (do_append){
			ret_val = write(fd, "x", 1);
			if (ret_val == -1){
				exit_error("append writing failed");
			}
		}else{
			ret_val = lseek(fd, 0, SEEK_END);
			if (ret_val == -1){
				exit_error("seek failed");
			}
			ret_val = write(fd, "x", 1);
			if (ret_val == -1){
				exit_error("non append writing failed");
			}

		}
		
	}
	close(fd);

	return 0;
}

void usage(){
	fprintf(stderr, "<program> filename num-bytes [x]\n");
	exit(1);
}
