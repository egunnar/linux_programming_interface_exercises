/*
 Implement readv() and writev() using read(), write(), and suitable functions from the malloc package (Allocating Memory on the Heap: malloc() and free()). 

struct iovec {
	void  *iov_base;     Starting address 
	size_t iov_len;      Number of bytes to transfer 
};

ssize_t readv(int fd, const struct iovec *iov, int iovcnt);
ssize_t writev(int fd, const struct iovec *iov, int iovcnt);
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/uio.h>
#include <assert.h>


int main(int argc, char *argv[]){

	struct iovec a;
	char * contents1 = "hello ";
	a.iov_base = malloc(strlen(contents1));
	strcpy(a.iov_base, contents1);
	a.iov_len = strlen(contents1); 
	
	struct iovec b;
	char * contents2 = "world";
	b.iov_base = malloc(strlen(contents2));
	strcpy(b.iov_base, contents2);
	b.iov_len = strlen(contents2); 

	struct iovec * iovec_ptr = &a;

	mode_t permission_mode = S_IROTH | S_IWOTH | S_IRUSR | S_IWUSR | 
		S_IRGRP | S_IWGRP;
	int open_flag = O_WRONLY | O_CREAT;
	int fd_write = open("5_7_tmp.txt", open_flag, permission_mode);
	my_writev(fd_write, iovec_ptr, 2);
	close(fd_write);

	// now see if can read in the same file
	struct iovec in[2];
	in[0].iov_base = malloc(strlen(contents1));
	in[0].iov_len = strlen(contents1);
	in[1].iov_base = malloc(strlen(contents2));
	in[1].iov_len = strlen(contents2);

	char test_out[100];
	int fd_read = open("5_7_tmp.txt", O_RDONLY);
	int bytes_read = my_readv(fd_read, in, 2);
	fprintf(stderr, "bytes read:%d\n", bytes_read);
	// works to here
	fprintf(stderr, "ok 1\n");
	strcpy(test_out, in[0].iov_base);
	fprintf(stderr, "ok 2\n");
	strcat(test_out, in[1].iov_base);
	assert(strcmp(test_out, "hello world") == 0);
}


// FIXME this is suppose to atomic ?
int my_readv(int fd, const struct iovec *iov, int iovcnt){
	int bytes_read = 0;
	int i;
	for (i = 0; i != iovcnt; ++i){
		bytes_read += read(fd, iov->iov_base, iov->iov_len);
		iov++;
	}
	return bytes_read;
}

int my_writev(int fd, const struct iovec *iov, int iovcnt){
	int bytes_written = 0;
	int i;
	for (i = 0; i != iovcnt; ++i){
		bytes_written += write(fd, iov->iov_base, iov->iov_len);
		iov++;
	}
	return bytes_written;
}
