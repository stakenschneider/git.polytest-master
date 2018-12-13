#include <iostream>
#include <windows.h>

int main(const int argc, const char** argv) {
	__try {

		// Если первый аргумент равен '1', то выходим через goto, если нет, то через __leave.
		const auto isGoto = argc > 1 && std::strcmp(argv[1], "1") == 0;
		if(isGoto)
			goto out;
		else
			__leave;

		// Программа должна завершиться до вызова исключения.
		RaiseException(EXCEPTION_FLT_OVERFLOW, NULL, NULL, nullptr);
	} __except(EXCEPTION_EXECUTE_HANDLER) {
		std::cout << "Exception!" << std::endl;
		return 0x1;
	}

out:
	std::cout << "Without exception!" << std::endl;
	return 0x0;
}