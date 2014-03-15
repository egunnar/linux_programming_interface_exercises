/* implement dup() and dup2() using fcntl */
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]){

	// test my_dup
	int new_fd = my_dup(1);
	char * message = "testing my_dup against stdout\n";
	fprintf(stderr, "my_dup returned:%d\n", new_fd);
	write(new_fd, message, strlen(message));

	// test my_dup2 basic usage
	int new_file_fd = 5;
	int ret = my_dup2(1, new_file_fd);
	fprintf(stderr, "\nmy_dup2 returned:%d\n", ret);
	message = "testing my_dup2 against stdout\n";
	write(ret, message, strlen(message));

	// test my_dup2 same file descriptor 
	ret = my_dup2(new_file_fd, new_file_fd);
	fprintf(stderr, "\n2nd test my_dup2 returned:%d\n", ret);
	message = "2nd test testing my_dup2 against stdout\n";
	write(ret, message, strlen(message));

	// test my_dup2 same file descriptor with a invalid file descriptor
	ret = my_dup2(100, 100);
	fprintf(stderr, "\n3rd test my_dup2 returned:%d\n", ret);
	fprintf(stderr, "the error message:%s\n", strerror(errno));
	
	return 0;
}

/* returns the newest unused file descriptor or -1 if a error
 */
int my_dup(int fd){
	int new_fd = fcntl(fd, F_DUPFD, 0);	
	if (new_fd == -1){
    	fprintf(stderr, "%s\n", strerror(errno));
	}
	return new_fd;
}

/* 
make a duplicate of old_fd in the number supplied in new_fd.
if new_fd is open, close it first. a successfull call to 
function returns new_fd
*/ 
int my_dup2(int old_fd, int new_fd){
	int ret;
	if (old_fd == new_fd){
		ret = fcntl(old_fd, F_GETFL);		
		if (ret == -1){
			errno = EBADF;
			return -1;
		}
		// no need to do anything
		return old_fd;
	}

	close(new_fd);
	ret = fcntl(old_fd, F_DUPFD, new_fd);	
	return ret;
}

