#include <stdio.h>      // printf()
#include <unistd.h>     // sleep()
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define  KEY_NUM     9999 
#define  MEM_SIZE    1024

int main( void)
{
        int   shm_id;
        int   num, index;
        char  buf1[MEM_SIZE];
        char  buf2[MEM_SIZE];
	int   *buf;
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

        buf = (int*)shm_addr;
	buf[255]=1;	
        printf("Shmem is set, write the number that you want to insert \n");
	fgets(buf1, MEM_SIZE ,stdin);
	num = atoi(buf1);
	while(1)
	{
        	printf("Type the index number that you want to insert (0~250)\n");
		fgets(buf2,MEM_SIZE,stdin);
		index = atoi(buf2);
		if(index<0||index>250)
        		printf("Wrond index (0~250)\n");
		else
		{
			buf[252] = index;
			buf[253] = num;
			buf[254] = 1;
			break;
		}
	}
		
        buf[index] = num;
	
        return 0;
}

