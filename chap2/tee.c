#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>


int main(int argc, char *argv[]){

	bool do_append = false;
	int c;	
	char * file_name = "";

	while ((c = getopt(argc, argv, "a")) != -1 ){
		if (c == 'a'){
			do_append = true;
		}else if (c == '?'){
			exit(1);
		}
	}
	fprintf(stderr, "optind:%d\n", optind);

	file_name = argv[optind];

	if (do_append){
		fprintf(stderr, "do_append\n");
	}else{
		fprintf(stderr, "NO do_append\n");
	}
	fprintf(stderr, "file_name:%s\n", file_name);


	return 0;
}
