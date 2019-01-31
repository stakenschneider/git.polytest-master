#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <syslog.h>
#include <sys/mman.h>

void signalArythmeticHandler(const int signalCode) {
    const char* message = "Arythmetic exception occured! Code: 0x";
    printf("%s%x\n", message, signalCode);

    openlog("task3", 0, LOG_USER);
    syslog(LOG_NOTICE, "%s%x\n", message, signalCode);
    closelog();

    exit(EXIT_FAILURE);
}

void signalBusHandler(const int signalCode) {
    const char* message = "Bus exception occured! Code: 0x";
    printf("%s%x\n", message, signalCode);

    openlog("task3", 0, LOG_USER);
    syslog(LOG_NOTICE, "%s%x\n", message, signalCode);
    closelog();

    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 0x1;
    }

    struct sigaction arythmeticAction, busAction;

    arythmeticAction.sa_handler = signalArythmeticHandler;
    sigemptyset(&arythmeticAction.sa_mask);
    arythmeticAction.sa_flags;

    busAction.sa_handler = signalBusHandler;
    sigemptyset(&busAction.sa_mask);
    busAction.sa_flags;

    sigaction(SIGFPE, &arythmeticAction, NULL);
    sigaction(SIGBUS, &busAction, NULL);

    if (strcmp(argv[1], "0") == 0)
        raise(SIGFPE);
    else if (strcmp(argv[1], "1") == 0)
        raise(SIGBUS);

    return 0x0;
}
