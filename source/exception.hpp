#ifndef __PW_EXCEPTION_HPP__
#define __PW_EXCEPTION_HPP__

#include <exception>
#include <string>

namespace pw
{

    class contract
    {
        
    public:

        template<typename T>
        static void ensure(bool _contract, std::string _message)
        {
            if (!_contract) throw T(_message);
        }

    };

    class winapi_exception : public std::exception
    {

    public:

        winapi_exception();
        winapi_exception(const std::string &_what);

    };

    class invalid_operation_exception : public std::logic_error
    {

    public:

		invalid_operation_exception();
		invalid_operation_exception(const std::string &_what);

    };

    class argument_null_exception : public std::invalid_argument
    {

    public:

		argument_null_exception();
		argument_null_exception(const std::string &_what);

    };
}

//

#endif
