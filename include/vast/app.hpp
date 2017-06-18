#ifndef VAST_APP_HPP
#define VAST_APP_HPP

// Vast
#include <vast/heap.hpp>
#include <vast/window.hpp>
#include <vast/renderer.hpp>
#include <vast/scene.hpp>

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

		Window window;
		Renderer renderer;
		Scene scene;

	public:
		App(int argc, char* argv[]);
		int run();
		void close();
	};
}

#endif
