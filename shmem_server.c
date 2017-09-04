#include <stdio.h>      // printf()
#include <unistd.h>     // sleep()
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define  KEY_NUM     8000 
#define  MEM_SIZE    1024

int main( void)
{
   	int   shm_id;
   	char  buf_in[MEM_SIZE];
   	void *shm_addr;
   	int   count;

	if ( -1 == ( shm_id = shmget( (key_t)KEY_NUM, MEM_SIZE, IPC_CREAT|0666)))
   	{
      		printf( "shmget fail\n");
      		return -1;
   	}

   	if ( ( void *)-1 == ( shm_addr = shmat( shm_id, ( void *)0, 0)))
   	{
      		printf( "shmat fail\n");
      		return -1;
   	}

	while(1)
	{
		if(!strncmp((char*)shm_addr,"OK",2))
		{
			printf("write message to client\n");
   			fgets(buf_in, MEM_SIZE, stdin);
   			sprintf((char*)shm_addr, "%s", buf_in);	
		}
		else
		{
			while(!strcmp((char*)shm_addr,buf_in))
				;	
		}  
 	}
	return 0;
}
