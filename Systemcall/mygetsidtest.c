#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define __NR_mygetsid 437

int main(void){
	int *n;

	n=(int*)calloc(1,sizeof(int));
	printf("before buffer value : %d\n", *n);
	syscall(__NR_mygetsid, n);
	printf("after buffer value : %d\n", *n);

	printf("%s\n", strerror(errno));


	return 0;
}
