#include <iostream>
#include <windows.h>

DWORD filterException(const DWORD exceptionCode);

int main() {
	auto divider = 0, dividend = 1;
	auto number = dividend;
	__try {
		// Инициируем деление на ноль.
		number /= divider;
	} __except(filterException(GetExceptionCode())) {
		std::cerr << "Something goes wrong!" << number << std::endl;
		return 0x1;
	}

	return 0x0;
}

DWORD filterException(const DWORD exceptionCode) {
	return exceptionCode == EXCEPTION_INT_DIVIDE_BY_ZERO ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH;
}