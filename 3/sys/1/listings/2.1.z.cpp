#include <iostream>
#include <windows.h>

int main() {
	auto zero = 0, one = 1;
	__try {
		// Инициируем деление на ноль.
		const auto number = one / zero;
	} __except(GetExceptionCode() == EXCEPTION_INT_DIVIDE_BY_ZERO ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {
		std::cerr << "EXCEPTION_INT_DIVIDE_BY_ZERO: 0x" << std::hex << EXCEPTION_INT_DIVIDE_BY_ZERO << std::endl;
		return 0x1;
	}

	return 0x0;
}
