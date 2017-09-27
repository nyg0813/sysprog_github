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
        long mtype;                     /* message type, must be > 0 */
        int queue_type;                 /* 0 : Admin SQ */
                                        /* 1 : Admin CQ */
                                        /* 2 : SQ */
                                        /* 3 : CQ */
        int command;                    /* 0 : Read */
                                        /* 1 : Write */
                                        /* 2 : Trim */
        int index;                      // queue index
        unsigned long addr;             // target address
        char data[DATA_SIZE];           // data
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
		printf("Queue type is '%d' means that",msg.queue_type);
		if(msg.queue_type==0)
			printf(" Admin SQ\n");
		else if(msg.queue_type==1)
			printf(" Admin CQ\n");
		else if(msg.queue_type==2)
			printf(" SQ\n");
		else if(msg.queue_type==3)
			printf(" CQ\n");
		else
			printf(" error\n");
			
		printf("Command is '%d' means that",msg.command);
		if(msg.command==0)
			printf(" Read\n");
		else if(msg.command==1)
			printf(" Write\n");
		else if(msg.command==2)
			printf(" TRIM\n");
		else
			printf(" error\n");
		
		printf("Index is '%d'\n",msg.index);
		printf("Addr is '%x'\n",msg.addr); 
		printf("Data is '%s'\n", msg.data); 
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

