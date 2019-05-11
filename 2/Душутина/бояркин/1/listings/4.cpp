#include <iostream>
#include <sys/sysinfo.h>

static const int MEGABYTE_IN_BYTES = 1024 * 1024;
static const int MINUTE_IN_SECONDS = 60;
static const int HOUR_IN_SECONDS = MINUTE_IN_SECONDS * 60;
static const int DAY_IN_SECONDS = HOUR_IN_SECONDS * 24;

int main() {
    struct sysinfo information;
    sysinfo(&information);

    std::cout << "Time since boot: days " << information.uptime / DAY_IN_SECONDS << ", "
                                          << (information.uptime % DAY_IN_SECONDS) / HOUR_IN_SECONDS << ":"
                                          << (information.uptime % HOUR_IN_SECONDS) / MINUTE_IN_SECONDS << ":"
                                          << information.uptime % MINUTE_IN_SECONDS << std::endl;

    std::cout << "Total RAM: " << information.totalram / MEGABYTE_IN_BYTES << " Mb" << std::endl;
    std::cout << "Free RAM: " << information.freeram / MEGABYTE_IN_BYTES << " Mb" << std::endl;
    std::cout << "Process count: " << information.procs << std::endl;
    return 0x0;
}
