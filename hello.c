#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	pid_t pid;

	if ((pid = fork()) < 0) {
		fprintf(stderr, "fork error\n");
	} else if (pid == 0) {  /* specify pathname, specify environment */
		execl( "/bin/ls", "/bin/ls", NULL); 
		printf("I’m Child PID = %d, Parent PID =%d\n", getpid(), getppid());	
		
	}

//	if (waitpid(pid, NULL, 0) < 0)
//		fprintf(stderr, "wait error\n");

	if ((pid = fork()) < 0) {
		fprintf(stderr, "fork error\n");
	} else if (pid == 0) {  /* specify filename, inherit environment */
//		system("/bin/ls -a"); 
		printf("I’m Child PID = %d, Parent PID =%d\n", getpid(), getppid());	
	}
	exit(0); 
}

