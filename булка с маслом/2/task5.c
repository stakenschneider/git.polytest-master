#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <syslog.h>

void signalArythmeticHandler(const int signalCode) {
    printf("Arythmetic exception occured! Code: 0x%x\n", signalCode);

    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGBUS);
    sigprocmask(SIG_SETMASK, &sigset, NULL);

    raise(SIGBUS);

    printf("Next signal in queue.\n");
}

void signalBusHandler(const int signalCode) {
    printf("Bus exception occured! Code: 0x%x\n", signalCode);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (signal(SIGFPE, signalArythmeticHandler) == SIG_ERR)
        return 0x1;

    if (signal(SIGBUS, signalBusHandler) == SIG_ERR)
        return 0x2;

    raise(SIGFPE);
    return 0x0;
}
