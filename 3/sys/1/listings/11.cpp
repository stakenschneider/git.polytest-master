#include <iostream>
#include <windows.h>

int main(const int argc, const char** argv) {
	if(argc != 2 || std::strlen(argv[1]) != 1)
		return 0x1;

	__try {
		std::cout << "Try block." << std::endl;

		switch(argv[1][0]) {
			case '0':
				// Самостоятельное завершение __try.
				break;

			case '1':
				// Нормальное завершение __try.
				__leave;

			case '2':
				// Безусловное завершение __try.
				goto out;

			case '3':
				// Завершение __try с исключением.
				RaiseException(EXCEPTION_FLT_OVERFLOW, NULL, NULL, nullptr);
				break;

			case '4':
				// Завершение __try выходом из функции.
				return 0x0;

			default:
				return 0x2;
		}
	} __finally {
		std::cout << "Finally block." << std::endl;

		if(AbnormalTermination()) {
			std::cout << "Abnormal termination." << std::endl;
		} else {
			std::cout << "Normal termination." << std::endl;
		}
	}

out:
	return 0x0;
}