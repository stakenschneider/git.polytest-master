#include <iostream>
#include <windows.h>

EXCEPTION_RECORD exceptionRecord;

DWORD filterException(const DWORD exceptionCode, const EXCEPTION_POINTERS* exceptionPointers);

int main() {
	__try {
		RaiseException(EXCEPTION_INT_DIVIDE_BY_ZERO, NULL, NULL, nullptr);
	} __except(filterException(GetExceptionCode(), GetExceptionInformation())) {
		std::cerr << "EXCEPTION_INT_DIVIDE_BY_ZERO: 0x" << std::hex << EXCEPTION_INT_DIVIDE_BY_ZERO << std::endl;
		std::cout << "Exception code: 0x" << std::hex << exceptionRecord.ExceptionCode << std::endl;
		std::cout << "Exception flags: 0x" << std::hex << exceptionRecord.ExceptionFlags << std::endl;
		std::cout << "Exception record: 0x" << std::hex << exceptionRecord.ExceptionRecord << std::endl;
		std::cout << "Exception address: 0x" << std::hex << exceptionRecord.ExceptionAddress << std::endl;
		std::cout << "Number parameters: " << exceptionRecord.NumberParameters << std::endl;
		return 0x1;
	}

	return 0x0;
}

DWORD filterException(const DWORD exceptionCode, const EXCEPTION_POINTERS* exceptionPointers) {
	memcpy(&exceptionRecord, exceptionPointers->ExceptionRecord, sizeof(exceptionRecord));
	return exceptionCode == EXCEPTION_INT_DIVIDE_BY_ZERO ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH;
}