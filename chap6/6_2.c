/* Write a program to see what happens if we try to longjmp 
 * into a function that already returned 
 * The answer is the program gives a segmentation fault.
 * Strangely line 24 gets printed twice.
 * */

#include <setjmp.h>
#include <setjmp.h>
#include <stdio.h>

static jmp_buf env;

int main(int argc, char * argv[]){
	f();
	fprintf(stderr, "calling longjmp..\n");
	longjmp(env, 1);
	return 0;
}

void f(){
	fprintf(stderr, "in f() where calling setjmp\n");
	// note, i don't really do anything with the jump location
	int jump_location = setjmp(env);	
	fprintf(stderr, "setjmp returned:%d\n", jump_location);
}
