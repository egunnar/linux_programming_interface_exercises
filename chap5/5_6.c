/*
After each of the calls to write() in the following code, explain what the content of the output file would be, and why: 
fd1 = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
fd2 = dup(fd1);
fd3 = open(file, O_RDWR);
write(fd1, "Hello,", 6);
write(fd2, " world", 6);
lseek(fd2, 0, SEEK_SET); 
write(fd1, "HELLO,", 6); 
write(fd3, "Gidday", 6); 
*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char * argv[]){
	char * file = "test_5_6.txt";
	int fd1 = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	int fd2 = dup(fd1);
	int fd3 = open(file, O_RDWR);

	write(fd1, "Hello,", 6);
	// file will be "Hello,"

	write(fd2, " world", 6);
	// file will be "Hello, world"

	lseek(fd2, 0, SEEK_SET); 
	write(fd1, "HELLO,", 6); 
	// file will be "HELLO, world"

	write(fd3, "Gidday", 6); 
	// file will be "Gidday world"

}

