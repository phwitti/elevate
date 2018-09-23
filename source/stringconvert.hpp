#ifndef __PW_STRINGCONVERT_HPP__
#define __PW_STRINGCONVERT_HPP__

#include <codecvt>
#include <string>
#include "windows.hpp"

namespace pw
{
	struct stringconvert
	{
		static std::wstring widen(const std::string &_string)
		{
			if (_string.empty())
				return std::wstring();

			int size_needed = MultiByteToWideChar(CP_UTF8, 0, &_string[0], (int)_string.size(), NULL, 0);
			std::wstring wstring(size_needed, 0);
			MultiByteToWideChar(CP_UTF8, 0, &_string[0], (int)_string.size(), &wstring[0], size_needed);

			return wstring;
		}

		static std::string narrow(const std::wstring &_wstring)
		{
			if (_wstring.empty())
				return std::string();

			int size_needed = WideCharToMultiByte(CP_UTF8, 0, &_wstring[0], (int)_wstring.size(), NULL, 0, NULL, NULL);
			std::string string(size_needed, 0);
			WideCharToMultiByte(CP_UTF8, 0, &_wstring[0], (int)_wstring.size(), &string[0], size_needed, NULL, NULL);
			return string;
		}
	};
}

#endif
