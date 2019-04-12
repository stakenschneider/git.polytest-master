#include <stdexcept>
#include <iostream>

int main(int argc, char *argv[]) {
    try {
        try {
            try {
                throw std::out_of_range("");
            } catch (const std::length_error& exception) {
                // Unreachable code.
                std::cout << "Length error exception." << std::endl;
            }
        } catch (const std::out_of_range& exception) {
            std::cout << "Out of range exception." << std::endl;
            throw std::overflow_error("");
        }
    } catch (const std::overflow_error& exception) {
        std::cout << "Overflow exception." << std::endl;
    }

    return 0x0;
}
