#ifndef VAST_LOG_HPP
#define VAST_LOG_HPP

// Standard
#include <string>
#include <vector>

namespace Vast
{
	class Log
	{
	private:
		std::vector<std::string> logs;

	public:
		enum class Mode
		{
			DEBUG,
			INFO,
			WARNING,
			ERROR,
		};

		void write(std::string msg, Mode mode = Mode::DEBUG);
		void clear();
	};

	extern Log g_log;
}

#endif
