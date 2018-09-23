#ifndef __PW_PROCESS_HPP__
#define __PW_PROCESS_HPP__

#include <string>

#include "windows.hpp"

namespace pw
{
	class process
	{

	public:

		process(const std::string &_application_name, const std::string &_current_directory, bool _elevated = false);
		process(const std::string &_application_name, const std::string &_current_directory, const std::string &_parameters, bool _elevated = false);
		~process();

		void wait(float _timeout);
		
	private:

		const std::wstring c_verb_open_default = L"open";
		const std::wstring c_verb_open_elevated = L"runas";
		SHELLEXECUTEINFOW m_shell_execute_info;

	};
}

#endif
