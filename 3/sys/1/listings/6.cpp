#include <iostream>
#include <windows.h>

DWORD filterException(const DWORD exceptionCode, const DWORD exceptionExpect);

int main(const int argc, const char** argv) {
	__try {
		__try {
			// Если первый аргумент равен '1', то вызываем исключение EXCEPTION_FLT_OVERFLOW, если нет, то EXCEPTION_INT_DIVIDE_BY_ZERO.
			const auto exceptionCode = (argc > 1 && std::strcmp(argv[1], "1") == 0) ? EXCEPTION_FLT_OVERFLOW : EXCEPTION_INT_DIVIDE_BY_ZERO;
			RaiseException(exceptionCode, NULL, NULL, nullptr);
		}
		__except(filterException(GetExceptionCode(), EXCEPTION_INT_DIVIDE_BY_ZERO)) {
			std::cout << "EXCEPTION_INT_DIVIDE_BY_ZERO" << std::endl;
			return 0x1;
		}
	} __except(filterException(GetExceptionCode(), EXCEPTION_FLT_OVERFLOW)) {
		std::cout << "EXCEPTION_FLT_OVERFLOW" << std::endl;
		return 0x2;
	}

	return 0x0;
}

DWORD filterException(const DWORD exceptionCode, const DWORD exceptionExpect) {
	if(exceptionCode == exceptionExpect) {
		// Вызываем обработчик.
		std::cout << "EXCEPTION_EXECUTE_HANDLER" << std::endl;
		return EXCEPTION_EXECUTE_HANDLER;
	}

	// Продолжаем поиск обработчика выше.
	std::cout << "EXCEPTION_CONTINUE_SEARCH" << std::endl;
	return EXCEPTION_CONTINUE_SEARCH;
}