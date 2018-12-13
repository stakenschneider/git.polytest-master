#include <iostream>
#include <windows.h>

int main() {
	__try {
		RaiseException(EXCEPTION_FLT_OVERFLOW, NULL, NULL, nullptr);
	} __except(GetExceptionCode() == EXCEPTION_FLT_OVERFLOW ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {
		std::cerr << "EXCEPTION_FLT_OVERFLOW: 0x" << std::hex << EXCEPTION_FLT_OVERFLOW << std::endl;
		return 0x1;
	}

	return 0x0;
}