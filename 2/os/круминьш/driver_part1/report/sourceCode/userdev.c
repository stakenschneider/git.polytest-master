#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <linux/unistd.h> 

int main()
{ 
	int fd;
	size_t cnt = 0;
	size_t cnt2 = 0;
	char bufferIn[50] = "Hello, character device!";
	char bufferOut[50];

	printf("We work with character device driver\n");
	fd = open("/dev/chardev", O_RDWR);
	if (fd == -1) {
	 	printf("open failed\n");
	 	return -1;	
	}
	printf("Character driver open\n");
	
	cnt = write(fd, bufferIn, sizeof(bufferIn));
	printf("Character driver write %d bytes\n", cnt);

	cnt = read(fd, bufferOut, sizeof(bufferOut));
	printf("Character driver read %d bytes\n", cnt);
	int i =0;
	while ( i<cnt){
		printf("%c",bufferOut[i]);
		i++;
	}
	close(fd);
	printf("\nCharacter driver close\n");
	return 0;	
}
