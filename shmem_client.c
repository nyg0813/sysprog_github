#include <stdio.h>      // printf()
#include <unistd.h>     // sleep()
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define  KEY_NUM     8000
#define  MEM_SIZE    1024

int main( void)
{
	int   shm_id;
	char  buf_in[MEM_SIZE];
	int   buf[MEM_SIZE/sizeof(int)];
	void *shm_addr;
	while ( -1 == ( shm_id = shmget( (key_t)KEY_NUM, MEM_SIZE, 0666)))
		;
	
	printf( "ready to attach\n");

	if ( ( void *)-1 == ( shm_addr = shmat( shm_id, ( void *)0, 0)))
	{
		printf( "shmat fail\n");
		return -1;
	}

	strcpy(buf_in, (char*)shm_addr);
	while(1)
	{
		if(!strcmp(buf_in,(char*)shm_addr)&&strncmp((char*)shm_addr,"OK",2)!=0)
		{
			sprintf((char*)shm_addr, "%s", "OK");
			while(!strncmp((char*)shm_addr,"OK",2))
                                ;
			printf("server send\n");
			printf("%s",(char*)shm_addr);
		}
		else
		{	
			strcpy(buf_in, (char*)shm_addr);
		}
	}
	 
   	return 0;
}
