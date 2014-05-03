#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/*
Explain why the output of the following code differs depending on whether standard output is redirected to a terminal or to a disk file. 
printf("If I had more time, \n"); 
write(STDOUT_FILENO, "I would have written you a shorter letter.\n", 43);

Will print the printf statement first. Because stdout is open in a 
mode that flushed the buffer ( _IOLBF, see man setvbuf for more info )

*/

int main(int argc, char * argv[]){
	printf("If I had more time, \n"); 
	write(STDOUT_FILENO, "I would have written you a shorter letter.\n", 43); 
	
	fprintf(stderr, "\n");
	// this will reverse the order unlike the above
	printf("If I had more time, ");  // no new line
	write(STDOUT_FILENO, "I would have written you a shorter letter.\n", 43); 
	printf("\n");
}
