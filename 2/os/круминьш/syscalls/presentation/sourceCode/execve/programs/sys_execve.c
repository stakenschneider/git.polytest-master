#include <unistd.h>

int main(int argc, char* argv[], char* envp[])
{
	printf("Hello %s\n", argv[1]);

	int i=0;
	char* item = envp[i];
	while(item != NULL){
		printf("%d: %s\n", i, item);
		i++;
		item = envp[i];
	}	
}