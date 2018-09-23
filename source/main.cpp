
#include <iostream>

#include "action_map.hpp"
#include "process.hpp"

//

int main(int _argc, char *_argv[])
{
	// setup

	std::vector<std::string> arguments(_argv, _argv + _argc);

	const std::string c_runas_argument = "runas";
	const std::string c_command_line = "cmd";
	const std::string c_current_directory = ".";

	// Create a map that associates the command line arguments with their appropriate behaviour
	pw::action_map<std::string> action_map;
	action_map.emplace(c_runas_argument, [&]() {

		// with "runas"-argument: 
		//   we already are elevated, now start cmd

		pw::process(c_command_line, c_current_directory);
	});

	//

	// execute

	if (!action_map.execute_first(arguments))
	{
		try
		{
			// if no "runas"-argument provided: 
			//   restart elevate.exe with admin-rights (and "runas"-argument)

			// first command line argument should always be the executing command
			pw::process(arguments[0], c_current_directory, c_runas_argument, true);
		}
		catch (...)
		{
			// process creation fails if user declines administration-rights
			// - then just ignore
		}
	}

	return 0;
}
