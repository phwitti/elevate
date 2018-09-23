
#include "windows.hpp"
#include "exception.hpp"

namespace pw
{
    winapi_exception::winapi_exception()
        : std::exception([](){

            DWORD dwLastError = GetLastError();

            LPVOID lpMessageBuffer;
            FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, dwLastError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&lpMessageBuffer, 0, NULL);

            std::string message = (LPSTR)lpMessageBuffer;

            LocalFree(lpMessageBuffer);

            return message;

        }().c_str())
    {
    }

	winapi_exception::winapi_exception(const std::string &_what) : std::exception(_what.c_str())
    {
    }

    //

    invalid_operation_exception::invalid_operation_exception() : logic_error("An invalid operation occured.")
    {
    }

	invalid_operation_exception::invalid_operation_exception(const std::string &_what) : logic_error("<invalid_operation_exception> " + _what)
    {
    }

	//

    argument_null_exception::argument_null_exception() : invalid_argument("Argument may not be null.")
    {
    }

	argument_null_exception::argument_null_exception(const std::string &_what) : invalid_argument("<argument_null_exception>: " + _what)
    {
    }
}
