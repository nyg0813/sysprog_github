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
	ssize_t nbytes = 0;
	int msg_size = 0;
	msg_size = sizeof(msg) - sizeof(msg.mtype);
	nbytes =  msgrcv(que_id, &msg, msg_size, 2696, IPC_NOWAIT);
	if (nbytes > 0)
	{
		printf("recv msg form msgque, bytes(%lu)\n", nbytes); 
		printf("%s\n", msg.mtext); 
	}
	else
	{
		if (errno == ENOMSG) 
			printf("empty queue\n");
		else
		{
			printf("msgrcv() error\n");
			return -1;
		}
	}
	return 0;
}

