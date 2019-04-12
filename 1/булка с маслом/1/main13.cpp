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

LONG filter(EXCEPTION_POINTERS* exceptionPointers) {
	er = *(exceptionPointers->ExceptionRecord);
	return EXCEPTION_EXECUTE_HANDLER;
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

void throw_exception_datatype_misalignment()
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

void se_trans_func(unsigned code, EXCEPTION_POINTERS *info)
{
	throw *(info->ExceptionRecord);
}

int main()
{
	_set_se_translator(se_trans_func);
	try
	{
		throw_exception_divide_by_zero();
	}
	catch (EXCEPTION_RECORD record)
	{
		handle_exception(record.ExceptionCode);
	}
	try
	{
		throw_exception_datatype_misalignment();
	}
	catch (EXCEPTION_RECORD record)
	{
		handle_exception(record.ExceptionCode);
	}
	system("pause");
	return 0;
}


//EXCEPTION_NONCONTINUABLE_EXCEPTION 
//EXCEPTION_DATATYPE_MISALIGNMENT
