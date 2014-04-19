/*
Assume in each of the following cases that the initial set of process user IDs is real=1000 effective=0 saved=0 file-system=0. What would be the state of the user IDs after the following calls? 
setuid(2000); 
setreuid(-1, 2000); 
seteuid(2000);
setfsuid(2000);
setresuid(-1, 2000, 3000);

note I happen to be uid 1000
*/ 

#include <assert.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

// I want to run this program u+s (root)
int main(int argc, char * argv[]){

	assert_start();
	int ret = setuid(2000);
	assert(ret == 0);

	return 0;

}
void assert_ids(uid_t real_expected, uid_t effective_expected, uid_t saved_expected, uid_t file_system_expected){
	uid_t ruid; 
	uid_t euid; 
	uid_t suid;
	int ret = getresuid(&ruid, &euid, &suid);
	if (ret != 0){
		exit_err("getresuid failed\n");
	}
	assert(ruid == real_expected);
	assert(euid == effective_expected);
	assert(suid == saved_expected);
	// kind of pointless, but the exercise says to 
	// check the file system too
	assert(setfsuid(effective_expected) == effective_expected);
	printf("real:%d effective:%d saved:%d file-system:%d\n", ruid, euid, suid, euid);
}

void assert_start(){
	assert_ids(1000, 0, 0, 0);
}

void exit_err(char * msg){
	fprintf(stderr, msg);
	exit(0);
}

