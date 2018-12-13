#pragma warning(disable : 4996)

#include <iostream>
#include <windows.h>

void activateFloatExceptions();
DWORD filterException(const DWORD exceptionCode, float &wrongValue);

int main() {
	activateFloatExceptions();

	auto number = 1.f;
	__try {
		// Инициируем переполнение переменной с плавающей точкой.
		number = pow(1e3, 1e3);
	}
	__except(filterException(GetExceptionCode(), number)) {
		std::cerr << "Failed, number value is " << number << std::endl;
		return 0x1;
	}

	std::cerr << "Successfully, number value is " << number << std::endl;
	return 0x0;
}

void activateFloatExceptions() {
	// Включаем обработку исключений с плавающей точкой.
	auto control = _controlfp(NULL, NULL);
	control &= ~(EM_OVERFLOW | EM_UNDERFLOW | EM_INEXACT | EM_ZERODIVIDE | EM_DENORMAL);
	_controlfp(control, _MCW_EM);
}

DWORD filterException(const DWORD exceptionCode, float &wrongValue) {
	if(exceptionCode == EXCEPTION_FLT_OVERFLOW) {
		std::cout << "EXCEPTION_FLT_OVERFLOW: 0x" << std::hex << EXCEPTION_FLT_OVERFLOW << std::endl;
		std::cout << "Wrong float value: " << wrongValue << std::endl;
 
		// Не можем установить pow(1e3, 1e3), значит установим другое большое число.
		wrongValue = INT64_MAX;

		// Исключение корректно обработано, продолжаем выполнение программы.
		return EXCEPTION_CONTINUE_EXECUTION;
	}

	// Инициируем запуск обработчика.
	return EXCEPTION_EXECUTE_HANDLER;
}

