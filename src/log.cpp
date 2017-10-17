// Vast
#include <vast/log.hpp>

// Standard
#include <iostream>
#include <chrono>
#include <ctime>

namespace Vast
{
	Log g_log;

	void Log::write(std::string msg, Mode mode)
	{
		char buff[128];
		std::time_t now = std::time(nullptr);
		std::strftime(buff, sizeof(buff), "%H:%M:%S", std::localtime(&now));

		std::string log_entry = "[LOG @ " + std::string(buff) + "] " + msg;

		this->logs.push_back(log_entry);

		#ifndef DEBUG_BUILD
			if (mode != Mode::DEBUG)
		#endif
		{
			if (this == &g_log) // Are we the global log?
				std::cout << log_entry << std::endl;
		}
	}

	void Log::clear()
	{
		this->logs.clear();
	}
}
