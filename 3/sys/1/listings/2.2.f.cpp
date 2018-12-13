#pragma warning(disable : 4996)

#include <iostream>
#include <windows.h>

void activateFloatExceptions();

int main() {
	activateFloatExceptions();

	__try {
		// Инициируем переполнение переменной с плавающей точкой.
		pow(1e3, 1e3);
	} __except(EXCEPTION_EXECUTE_HANDLER) {
		const auto exceptionCode = GetExceptionCode();
		std::cerr << "EXCEPTION_CODE: 0x" << std::hex << exceptionCode << std::endl;
		return 0x1;
	}

	return 0x0;
}

void activateFloatExceptions() {
	// Включаем обработку исключений с плавающей точкой.
	auto control = _controlfp(NULL, NULL);
	control &= ~(EM_OVERFLOW | EM_UNDERFLOW | EM_INEXACT | EM_ZERODIVIDE | EM_DENORMAL);
	_controlfp(control, _MCW_EM);
}
