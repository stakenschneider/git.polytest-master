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


void handle_exception(DWORD code)
{
	std::cout << "Caught exception with code = " << code << std::endl;
	switch (code)
	{
	case EXCEPTION_INT_DIVIDE_BY_ZERO:
		std::cout << "EXCEPTION_INT_DIVIDE_BY_ZERO" << std::endl;
		break;
	case EXCEPTION_NONCONTINUABLE_EXCEPTION:
		std::cout << "EXCEPTION_NONCONTINUABLE_EXCEPTION" << std::endl;
		break;
	default:
		std::cout << "unrecognized exception" << std::endl;
		break;
	}
}

int main()
{
	__try
	{
		throw_exception_divide_by_zero();
	}
	__except (filter(GetExceptionCode(), EXCEPTION_INT_DIVIDE_BY_ZERO, GetExceptionInformation()))
	{
		std::cout << "Caught \"divide by zero\" exception\n" << std::endl;
		show_info();
	}
	std::cout << "\n\n\n" << std::endl;
	__try
	{
		throw_exception_noncontinuable();
	}
	__except (filter(GetExceptionCode(), EXCEPTION_NONCONTINUABLE_EXCEPTION, GetExceptionInformation()))
	{
		std::cout << "Caught \"noncontinuable exception\" exception\n" << std::endl;
		show_info();
	}
	return 0;
}


//EXCEPTION_NONCONTINUABLE_EXCEPTION 
//EXCEPTION_DATATYPE_MISALIGNMENT
