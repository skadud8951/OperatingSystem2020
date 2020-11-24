#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/syscalls.h>
#include <linux/string.h>
#include <linux/file.h>
#include <linux/module.h>
#include <linux/fcntl.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <asm/uaccess.h>


asmlinkage int sys_swrite(int fd, char* buf, int len){
 	struct file *file;
	loff_t pos = 0;
	unsigned char p;
	int j; 
	mm_segment_t old_fs = get_fs();
	set_fs(KERNEL_DS);
	int i;
	int k =0;
	char buf2[100]={"\0",};
	int x=1;
	int val=0;
	int count=0;
	char buf3[100] ={"\0",};
	      
	for(j =0; j<len; j++){
		p = 0x80;
		for(i=0; i<8; i++){
                	if(buf[j]&p){
                		buf2[k]=0;
			}
                	else{
                        	buf2[k]=1;		
                	}
		p = p>>1;
		k++;
		}
        }

	for(i=0; i<len;){
		for(j=7; j>=0; j--){
			val = val + x*buf2[i+j];
			x = x*2;
		}
		buf3[count]=x;
		x = 1;
		val =0;
		count++;
		i = i + 8;
	}
	*buf=buf3;

	if(fd>=0){
        	file = fget(fd);
		if(file){
			vfs_write(file, buf, len, &pos);
			fput(file);
		}

	}
	set_fs(old_fs);

        return len;
}

SYSCALL_DEFINE3(swrite, int, fd, char*, buf, int, len){

	return sys_swrite(fd, buf, len);
}
