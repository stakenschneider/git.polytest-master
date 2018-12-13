#include <iostream>
#include <windows.h>

EXCEPTION_RECORD exceptionRecord;

LONG WINAPI exceptionFilter(EXCEPTION_POINTERS* exceptionInformation);

int main() {
	// Устанавливаем обработчик исключений для всех необработанных исключений.
	const auto filterPointer = SetUnhandledExceptionFilter(exceptionFilter);
	std::cout << "OLD_EXCEPTION_HANDLER: 0x" << std::hex << filterPointer << std::endl
		      << "NEW_EXCEPTION_HANDLER: 0x" << std::hex << exceptionFilter << std::endl;

	RaiseException(EXCEPTION_FLT_OVERFLOW, NULL, NULL, nullptr);
	return 0x0;
}

LONG WINAPI exceptionFilter(EXCEPTION_POINTERS* exceptionInformation) {
	std::cout << "EXCEPTION_CODE: 0x" << std::hex << exceptionInformation->ExceptionRecord->ExceptionCode << std::endl;
	return EXCEPTION_EXECUTE_HANDLER;
}