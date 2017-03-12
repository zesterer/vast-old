#ifndef VAST_APP_HPP
#define VAST_APP_HPP

// Vast
#include <vast/heap.hpp>
#include <vast/window.hpp>
#include <vast/renderer.hpp>

// Standard
#include <string>
#include <vector>

namespace Vast
{
	class App
	{
	private:
		std::vector<std::string> args;

		bool running = false;

		Heap heap;
		Window window;
		Renderer renderer;

	public:
		App(int argc, char* argv[]);
		int run();
		void close();
	};
}

#endif
