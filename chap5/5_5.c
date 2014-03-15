#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* write a program to verify duplicated file descriptors
 * share a file offset value and open file status flags
 */


int main(int argc, char * argv[]){

	// make a file with some junk in it
	mode_t permission_mode = S_IROTH | S_IWOTH | S_IRUSR | S_IWUSR |
        S_IRGRP | S_IWGRP;
	int fd = open("dummy_data.txt", O_WRONLY | O_CREAT, permission_mode);
    if (fd == -1){
        fprintf(stderr, "openning dummy_data.txt failed");
    }
	char * str = "hello there";
	write(fd, str, strlen(str));

	int fd_offset = lseek(fd, 0, SEEK_CUR);
	fprintf(stderr, "fd_offset is:%d\n", fd_offset);
	int fd2 = dup(fd);

	int fd2_offset = lseek(fd2, 0, SEEK_CUR);

	// assert file offset value the same
	assert(fd2_offset == fd_offset);

	long fd1_flags = fcntl(fd, F_GETFD); 
	long fd2_flags = fcntl(fd2, F_GETFD); 

	// assert file status flags are the same
	assert(fd1_flags == fd2_flags);

	return 0;
}
