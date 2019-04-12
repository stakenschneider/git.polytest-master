#include <stdexcept>
#include <iostream>

int main(int argc, char *argv[]) {
    try {
        try {
            try {
                goto out;
            } catch (const std::length_error& exception) {
                std::cout << "Length error exception." << std::endl;
            }
        } catch (const std::out_of_range& exception) {
            std::cout << "Out of range exception." << std::endl;
        }
    } catch (const std::overflow_error& exception) {
        std::cout << "Overflow exception." << std::endl;
    }

    return 0x0;

out:
    std::cout << "Exit with goto instruction." << std::endl;
    return 0x0;
}
