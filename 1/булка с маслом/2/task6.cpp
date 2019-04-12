#include <stdexcept>
#include <iostream>

int main(int argc, char *argv[]) {
    try {
        throw std::out_of_range("Some C++ exception.");
    } catch (const std::out_of_range& exception) {
        std::cout << exception.what() << std::endl;
    }

    return 0x0;
}
