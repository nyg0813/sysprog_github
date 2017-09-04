// Example of message queue in C.
// For educational purposes only.
// Author: Vaclav Bohac

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


typedef struct {
	long mtype;     /* message type, must be > 0 */
	char mtext[16];  /* message data */
} MsgType;


int main ( void )
{
	key_t key = 4071;
	int que_id = msgget(key,0666);
	if(que_id==-1)
	{
		que_id = msgget(key, IPC_CREAT|0666);
		if(que_id==-1)
		{
			printf("msgget error\n");
			return -1;
		}
	}

	MsgType msg;
	int msg_size = 0;

	msg.mtype=2696; 
	strcpy(msg.mtext, "helloworld");

	msg_size = sizeof(msg) - sizeof(msg.mtype);

	int rtn = msgsnd(que_id, &msg, msg_size, IPC_NOWAIT);
	if (rtn == -1) {
		printf("msgsnd() fail\n");
		return -1;
	}
}


