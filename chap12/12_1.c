/*
Write a program that lists the process ID and command name for all processes being run by the user named in the program’s command-line argument. (You may find the userIdFromName() function from Example 8-1, in Example program, useful.) This can be done by inspecting the Name: and Uid: lines of all of the /proc/PID/status files on the system. Walking through all of the /proc/PID directories on the system requires the use of readdir(3), which is described in Section 18.8. Make sure your program correctly handles the possibility that a /proc/PID directory disappears between the time that the program determines that the directory exists and the time that it tries to open the corresponding /proc/PID/status file. 
*/

#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>

void usage(){
	fprintf(stderr, "enter user name to find all processes for\n");
	exit(1);
}

void process_status_file(char * status_file){
	FILE * fh = fopen(status_file, "r");
	char * line = NULL;
	size_t len = 0;
	ssize_t read;

	if (fh == NULL){
		printf(status_file);
		printf(" is no longer available\n");

	}
	char * pid_str = "Pid:\t";
	char * name_str = "Name:\t";
	char result[500];
	while ((read = getline(&line, &len, fh)) != -1) {
		if ((len >= strlen(pid_str)) && strncmp(line, pid_str, strlen(pid_str)) == 0){
			//result = line[strlen(pid_str)];
			strncpy(result, line, 499);
			result[len] = '\0';
			printf("%s ", result);
		}
		if ((len >= strlen(name_str)) && strncmp(line, name_str, strlen(name_str)) == 0){
			strncpy(result, line, 499);
			result[len] = '\0';
			printf("%s ", result);
		}
	}
	free(line);
}

int main(int argc, char* argv[]){

	DIR * open_dir;
	struct dirent *dp;

	if (argc != 2){
		usage();
	}
	char * username = argv[1];
	char status_file[500];
	
	open_dir = opendir("/proc");
	if (open_dir == NULL){
		fprintf(stderr, "couldn't open /proc directory\n");
	}
	while ((dp = readdir(open_dir)) != NULL){
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0){
			continue;           // Skip . and .. 
		}
		if (dp->d_type != DT_DIR){
			continue;
		}
		if (is_directory_all_digits(dp->d_name)){
			strcpy(status_file, "/proc/");
			strncat(status_file, dp->d_name, strlen(dp->d_name));
			strcat(status_file, "/status");
			process_status_file(status_file);
		}
	}
	closedir(open_dir);
}

int is_directory_all_digits(char * dir_name){
	int i = 0;
	while (dir_name[i] != '\0'){
		if (! isdigit(dir_name[i]))
			return 0;
		i++;
	}
	return 1;
}
