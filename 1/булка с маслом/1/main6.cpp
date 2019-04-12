#include <iostream>
#include <windows.h>

EXCEPTION_RECORD er;


LONG filter(DWORD actual_code, DWORD expected_code)
{
	if (actual_code == expected_code)
	{
		return EXCEPTION_EXECUTE_HANDLER;
	}
	else
	{
		return EXCEPTION_CONTINUE_SEARCH;
	}
}

LONG filter(DWORD actualCode, DWORD expectedCode, EXCEPTION_POINTERS* exceptionPointers)
{
	er = *(exceptionPointers->ExceptionRecord);
	return filter(actualCode, expectedCode);
}

void show_info()
{
	std::cout << "code: " << er.ExceptionCode << std::endl;
	std::cout << "flags: " << er.ExceptionFlags << std::endl;
	std::cout << "address: " << er.ExceptionAddress << std::endl;
	std::cout << "record: " << er.ExceptionRecord << std::endl;
	std::cout << "NumberParameters: " << er.NumberParameters << std::endl;
}

int throw_exception_divide_by_zero()
{
	int one = 1;
	int zero = 0;
	return one / zero;
}

void throw_exception_noncontinuable()
{
	RaiseException(EXCEPTION_NONCONTINUABLE_EXCEPTION, NULL, NULL, nullptr);
}


LONG filterWithPrint(PEXCEPTION_POINTERS exceptionPointers)
{
	er = *(exceptionPointers->ExceptionRecord);
	show_info();
	system("pause");
	return EXCEPTION_EXECUTE_HANDLER;
}

int main()
{
	auto old_filter = SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)filterWithPrint);
	throw_exception_noncontinuable();
	std::cout << "After exception" << std::endl;
	system("pause");
	return 0;
}


//EXCEPTION_NONCONTINUABLE_EXCEPTION 
//EXCEPTION_DATATYPE_MISALIGNMENT
