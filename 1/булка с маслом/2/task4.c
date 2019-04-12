#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <syslog.h>

void signalArythmeticHandler(const int signalCode) {
    const char* message = "Arythmetic exception occured! Code: 0x";
    printf("%s%x\n", message, signalCode);
    raise(SIGBUS);

    printf("Unreachable code, signals not in queue.\n");
    exit(EXIT_FAILURE);
}

void signalBusHandler(const int signalCode) {
    const char* message = "Bus exception occured! Code: 0x";
    printf("%s%x\n", message, signalCode);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    struct sigaction arythmeticAction, busAction;

    arythmeticAction.sa_handler = signalArythmeticHandler;
    sigemptyset(&arythmeticAction.sa_mask);
    arythmeticAction.sa_flags;

    busAction.sa_handler = signalBusHandler;
    sigemptyset(&busAction.sa_mask);
    busAction.sa_flags;

    sigaction(SIGFPE, &arythmeticAction, NULL);
    sigaction(SIGBUS, &busAction, NULL);

    raise(SIGFPE);
    return 0x0;
}
