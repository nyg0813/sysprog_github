#include <stdio.h>      // printf()
#include <unistd.h>     // sleep()
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define  KEY_NUM     9999
#define  MEM_SIZE    1024

int main( void)
{
	int   shm_id;
	char  buf_in[MEM_SIZE];
	int*  buf;
	void *shm_addr;
	while ( -1 == ( shm_id = shmget( (key_t)KEY_NUM, MEM_SIZE, 0666)))
		;
	
	printf( "ready to attach\n");

	if ( ( void *)-1 == ( shm_addr = shmat( shm_id, ( void *)0, 0)))
	{
		printf( "shmat fail\n");
		return -1;
	}

	buf=(int*)shm_addr;

	while(buf[255]!=1)
		;
	buf[255]=0;
	printf("Shmem is set\n");
	
	while(buf[254]!=1)
		;
	printf("Server Set index!\n");
	printf("There will be '%d' set on index '%d'\n",buf[253],buf[252]);
	int temp = buf[252];
	printf("Result of buf[%d] is '%d'\n",buf[252],buf[temp]);
	buf[252] = 0;
	buf[253] = 0 ;
	buf[254] = 0 ;
   	return 0;
}
