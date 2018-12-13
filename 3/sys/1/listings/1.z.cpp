#include <iostream>
#include <windows.h>

int main() {
	__try {
		RaiseException(EXCEPTION_INT_DIVIDE_BY_ZERO, NULL, NULL, nullptr);
	} __except(GetExceptionCode() == EXCEPTION_INT_DIVIDE_BY_ZERO ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {
		std::cerr << "EXCEPTION_INT_DIVIDE_BY_ZERO: 0x" << std::hex << EXCEPTION_INT_DIVIDE_BY_ZERO << std::endl;
		return 0x1;
	}

	return 0x0;
}