#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/mman.h>

void generateArythmeticException() {
    const int one = 1;
    const int zero = 0;
    const int exception = one  / zero;
}

void generateBusException() {
    FILE *f = tmpfile();
    int *m = mmap(0, 4, PROT_WRITE, MAP_PRIVATE, fileno(f), 0);
    *m = 0;
}

int main(int argc, char *argv[]){
    if (argc != 2) {
        return 0x1;
    }

    if (strcmp(argv[1], "0") == 0)
        generateArythmeticException();
    else if (strcmp(argv[1], "1") == 0)
        generateBusException();

    return 0x0;
}
