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


#define DATA_SIZE 4096

typedef struct MsgType{
	long mtype;     		/* message type, must be > 0 */
	int queue_type;			/* 0 : Admin SQ */
					/* 1 : Admin CQ */
					/* 2 : SQ */
					/* 3 : CQ */
	int command;			/* 0 : Read */
					/* 1 : Write */
					/* 2 : Trim */
	int index;			// queue index
	unsigned long addr;		// target address
	char data[DATA_SIZE];		// data
}MsgType;

void init_msg(struct MsgType* msg)
{
	msg->mtype 	= 0;
	msg->queue_type	= -1;
	msg->command	= -1;
	msg->index	= 0;
	msg->addr	= 0x00000000;
	strcpy(msg->data,"data");
}

void set_msg(struct MsgType* msg, long mtype, int qtype, int command, int index, unsigned long addr, char* data)
{
	msg->mtype 	= mtype;
	msg->queue_type= qtype;
	msg->command	= command;
	msg->index	= index;
	msg->addr	= addr;
	strcpy(msg->data,data);
}
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

	init_msg(&msg);
	
	set_msg(&msg,2696,3,1,0,0x80000000,"hello world");	

	msg_size = sizeof(msg) - sizeof(msg.mtype);

	int rtn = msgsnd(que_id, &msg, msg_size, IPC_NOWAIT);
	if (rtn == -1) {
		printf("msgsnd() fail\n");
		return -1;
	}
}


