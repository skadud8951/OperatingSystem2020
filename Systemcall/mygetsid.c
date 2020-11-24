#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/syscalls.h>

asmlinkage long sys_mygetsid(int* buffer){
	printk("before buffer value: %d\n", *buffer);
	*buffer = 2016113566;
	printk("after buffer value: %d\n", *buffer);
	return 0;
}
SYSCALL_DEFINE1(mygetsid, int*, n){
	return sys_mygetsid(n);
}

