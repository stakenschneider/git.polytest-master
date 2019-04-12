#include <iostream>
#include <unistd.h>

static const int DIRECTORY_PATH_SIZE = 1024;
static const char* DIRECTORY_PATH = "/home";

static char currentDirectory[DIRECTORY_PATH_SIZE];

const char* getCurrentDirectory();

int main() {
    std::cout << "Current directory: " << getCurrentDirectory() << std::endl;
    chdir(DIRECTORY_PATH);
    std::cout << "Current directory after chdir: " << getCurrentDirectory() << std::endl;
    return 0x0;
}

const char* getCurrentDirectory() {
    char* result = getcwd(currentDirectory, DIRECTORY_PATH_SIZE);

    if (result == NULL) {
        return NULL;
    }

    return currentDirectory;
}
