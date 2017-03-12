#ifndef VAST_WINDOW_HPP
#define VAST_WINDOW_HPP

// Vast
#include <vast/inputstate.hpp>

// Library
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

// Standard
#include <string>

namespace Vast
{
	class Window
	{
	private:
		GLFWwindow* window = nullptr;
		InputState inputstate;

	public:
		bool isOpen() const;
		const InputState& getInputState() { return this->inputstate; }

		bool open(std::string title);
		void display();
		void handleInput();
		void close();
	};
}

#endif
