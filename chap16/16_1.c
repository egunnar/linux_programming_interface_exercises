#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/xattr.h>
#include <string.h>

/* Write a program that can be used to create or modify a user EA for a file (i.e, a simple version of setfattr(1)). Then filename and the EA name and values should be supplied as command line arguments to the program. 
 * 
 * test this with:
 * $ ./a.out test.txt user.ea_name got_it
 * $ getfattr -d test.txt 
 * # file: test.txt
 * user.ea_name="got_it"
 *
 * $
 * */

void usage(){
	fprintf(stderr, "Requires exactly 3 command line arguments: the file name, the extended attribute name, and the extend attribute value\n");
	exit(1);
}

int main(int argc, char * argv[]){
	if (argc != 4){
		usage();
	}
	char * file_name = argv[1];
	printf("file_name:%s\n", file_name);
	char * ea_name = argv[2];
	printf("ea_name:%s\n", ea_name);
	char * ea_val = argv[3];
	printf("ea_val:%s\n", ea_val);

	int size = strlen(ea_val);
	if (setxattr(file_name, ea_name, ea_val, size, 0)	== -1){
		fprintf(stderr, "%s\n", strerror(errno));
		exit(1);
	}
	
	return 0;
}
