// Vast
#include <vast/window.hpp>
#include <vast/log.hpp>

// Library
#include <glbinding/gl/gl.h>

namespace Vast
{
	bool Window::isOpen() const
	{
		return !glfwWindowShouldClose(this->window);
	}

	bool Window::open(std::string title)
	{
		// Something went badly wrong if this fails
		if (!glfwInit())
		{
			g_log.write("Error : GLFW failed to initiate", Log::Mode::ERROR);
			return false;
		}

		// Set OpenGL window hint for OpenGL version
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, (int)gl::GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// Create the window
		this->window = glfwCreateWindow(800, 600, title.c_str(), NULL, NULL);

		// Check the window opened properly
		if (this->window == nullptr)
		{
			g_log.write("Error : Window creation failed", Log::Mode::ERROR);
			glfwTerminate();
			return false;
		}
		else
			g_log.write("Window with title '" + title + "' opened");

		// Find window OpenGL context version
		int vmaj = glfwGetWindowAttrib(this->window, GLFW_CONTEXT_VERSION_MAJOR);
		int vmin = glfwGetWindowAttrib(this->window, GLFW_CONTEXT_VERSION_MAJOR);
		int vrev = glfwGetWindowAttrib(this->window, GLFW_CONTEXT_VERSION_MAJOR);
		int vcore = glfwGetWindowAttrib(this->window, GLFW_OPENGL_PROFILE);

		g_log.write(
			std::string("OpenGL context version is '") +
			((vcore == GLFW_OPENGL_CORE_PROFILE) ? "Core" : "Compatible") + " " +
			std::to_string(vmaj) + "." +
			std::to_string(vmin) + "." +
			std::to_string(vrev) + "'"
		);

		// Set the current OpenGL context to this window's context
		glfwMakeContextCurrent(this->window);
		g_log.write("Activated OpenGL window context");

		// Input
		this->setCursorTrapped(true);

		return true;
	}

	void Window::display()
	{
		glfwSwapBuffers(this->window);
	}

	void Window::receiveInput()
	{
		// Poll window events
		glfwPollEvents();

		// Cursor
		if (this->cursor_trapped)
		{
			int width, height;
			double cursor_x, cursor_y;
			glfwGetWindowSize(this->window, &width, &height);
			glfwGetCursorPos(this->window, &cursor_x, &cursor_y);

			this->centreCursor();

			// Find the amount the cursor has moved since the last reset
			this->inputstate.setCursorOffset(glm::vec2(cursor_x - width / 2, cursor_y - height / 2));
		}
		else
			this->inputstate.setCursorOffset(glm::vec2(0));

		// Update the input state depending on keys
		this->inputstate.setKeyState(InputState::Key::MOVE_UP    , glfwGetKey(this->window, GLFW_KEY_UP) == GLFW_PRESS);
		this->inputstate.setKeyState(InputState::Key::MOVE_LEFT  , glfwGetKey(this->window, GLFW_KEY_LEFT) == GLFW_PRESS);
		this->inputstate.setKeyState(InputState::Key::MOVE_DOWN  , glfwGetKey(this->window, GLFW_KEY_DOWN) == GLFW_PRESS);
		this->inputstate.setKeyState(InputState::Key::MOVE_RIGHT , glfwGetKey(this->window, GLFW_KEY_RIGHT) == GLFW_PRESS);

		this->inputstate.setKeyState(InputState::Key::MOVE_CROUCH, glfwGetKey(this->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS);
		this->inputstate.setKeyState(InputState::Key::MOVE_JUMP  , glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS);

		this->inputstate.setKeyState(InputState::Key::MOVE_SFORWARD , glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS);
		this->inputstate.setKeyState(InputState::Key::MOVE_SLEFT    , glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS);
		this->inputstate.setKeyState(InputState::Key::MOVE_SBACKWARD, glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS);
		this->inputstate.setKeyState(InputState::Key::MOVE_SRIGHT   , glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS);
		this->inputstate.setKeyState(InputState::Key::MOVE_SCCW     , glfwGetKey(this->window, GLFW_KEY_Q) == GLFW_PRESS);
		this->inputstate.setKeyState(InputState::Key::MOVE_SCW      , glfwGetKey(this->window, GLFW_KEY_E) == GLFW_PRESS);
	}

	void Window::setCursorTrapped(bool trapped)
	{
		this->cursor_trapped = trapped;

		if (this->cursor_trapped)
		{
			glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			this->centreCursor();
		}
		else
			glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	void Window::centreCursor()
	{
		int width, height;
		glfwGetWindowSize(this->window, &width, &height);
		glfwSetCursorPos(this->window, width / 2, height / 2);
	}

	void Window::close()
	{
		glfwTerminate();
		g_log.write("Closed window");
	}
}
