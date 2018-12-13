#include <iostream>
#include <windows.h>

int main() {
	auto zero = 0, one = 1;
	__try {
		// Инициируем деление на ноль.
		const auto number = one / zero;
	} __except(EXCEPTION_EXECUTE_HANDLER) {
		const auto exceptionCode = GetExceptionCode();
		std::cerr << "EXCEPTION_CODE: 0x" << std::hex << exceptionCode << std::endl;
		return 0x1;
	}

	return 0x0;
}
