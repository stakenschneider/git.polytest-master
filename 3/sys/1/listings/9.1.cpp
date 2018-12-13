#include <iostream>
#include <windows.h>

void translator(const UINT exceptionCode, EXCEPTION_POINTERS* exceptionInformation);

int main() {
	// Работает только со включенной опцией /EHa в компиляторе VS.
	_set_se_translator(translator);

	try {
		RaiseException(EXCEPTION_FLT_OVERFLOW, NULL, NULL, nullptr);
	} catch(const UINT exceptionCode) {
		std::cout << "EXCEPTION_FLT_OVERFLOW: 0x" << std::hex << exceptionCode << std::endl;
		return 0x2;
	}

	return 0x0;
}

void translator(const UINT exceptionCode, EXCEPTION_POINTERS* exceptionInformation) {
	throw exceptionCode;
}