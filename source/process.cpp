#include "process.hpp"

#include <cmath>

#include "stringconvert.hpp"
#include "exception.hpp"

namespace pw
{
	process::process(const std::string &_application_name, const std::string &_current_directory, bool _elevated) :
		process(_application_name, _current_directory, std::string(), _elevated)
	{
	}

	process::process(const std::string &_application_name, const std::string &_current_directory, const std::string &_parameters, bool _elevated)
	{
		STARTUPINFO startupinfo;
		ZeroMemory(&startupinfo, sizeof(STARTUPINFO));
		startupinfo.cb = sizeof(STARTUPINFO);

		std::wstring w_application_name = pw::stringconvert::widen(_application_name);
		std::wstring w_parameters = pw::stringconvert::widen(_parameters);
		std::wstring w_current_directory = pw::stringconvert::widen(_current_directory);

		m_shell_execute_info = { 0 };
		m_shell_execute_info.cbSize = sizeof(m_shell_execute_info);
		m_shell_execute_info.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_NO_CONSOLE;
		m_shell_execute_info.hwnd = 0;
		m_shell_execute_info.lpVerb = (_elevated ? c_verb_open_elevated : c_verb_open_default).c_str();
		m_shell_execute_info.lpFile = w_application_name.c_str();
		m_shell_execute_info.lpParameters = w_parameters.empty() ? NULL : w_parameters.c_str();
		m_shell_execute_info.lpDirectory = w_current_directory.c_str();
		m_shell_execute_info.nShow = SW_SHOW;
		m_shell_execute_info.hInstApp = 0;
			 
		if (!ShellExecuteExW(&m_shell_execute_info))
		{
			throw pw::winapi_exception();
		}
	}

	process::~process()
	{
		CloseHandle(m_shell_execute_info.hProcess);
	}

	void process::wait(float _timeout)
	{
		if (_timeout < 0.0f)
			_timeout = 0.0f;

		if (std::isinf(_timeout))
		{
			WaitForSingleObject(m_shell_execute_info.hProcess, INFINITE);
		}
		else
		{
			WaitForSingleObject(m_shell_execute_info.hProcess, static_cast<DWORD>(_timeout * 1000.0f));
		}
	}
}
