#include <stdio.h>
#include <unistd.h>

int func(int i);

int main ()
{
	int a;
	int i=0;
	int b=0;
	while(i<10){
		int f=1;
		static int d=1;
		d++;
		f++;
		i++;
		printf("d: %d, f: %d\n", d, f);
	}

	func(1);

	return 0;
	
}

int func(int i)
{
	if(i<10){
		i++;
		return func(i);
	}
	else{
		printf("Last value: %d\n",i);	
		return 0;
	}
}

