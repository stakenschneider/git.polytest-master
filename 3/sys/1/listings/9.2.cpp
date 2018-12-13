#include <iostream>
#include <windows.h>

void translator(const UINT exceptionCode, EXCEPTION_POINTERS* exceptionInformation);

int main() {
	// Работает только со включенной опцией /EHa в компиляторе VS.
	_set_se_translator(translator);

	try {
		RaiseException(EXCEPTION_FLT_OVERFLOW, NULL, NULL, nullptr);
	} catch(const EXCEPTION_POINTERS* exceptionInformation) {
		const auto exceptionRecord = exceptionInformation->ExceptionRecord;
		std::cout << "Exception code: 0x" << std::hex << exceptionRecord->ExceptionCode << std::endl;
		std::cout << "Exception flags: 0x" << std::hex << exceptionRecord->ExceptionFlags << std::endl;
		std::cout << "Exception record: 0x" << std::hex << exceptionRecord->ExceptionRecord << std::endl;
		std::cout << "Exception address: 0x" << std::hex << exceptionRecord->ExceptionAddress << std::endl;
		std::cout << "Number parameters: " << exceptionRecord->NumberParameters << std::endl;
		return 0x2;
	}

	return 0x0;
}

void translator(const UINT exceptionCode, EXCEPTION_POINTERS* exceptionInformation) {
	EXCEPTION_POINTERS result;
	std::memcpy(&result, exceptionInformation, sizeof(result));
	throw &result;
}