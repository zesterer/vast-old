// Vast
#include <vast/window.hpp>
#include <vast/log.hpp>

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

			// Create the window
		this->window = glfwCreateWindow(640, 480, title.c_str(), NULL, NULL);

		// Check the window opened properly
		if (this->window == nullptr)
		{
			g_log.write("Error : Window creation failed", Log::Mode::ERROR);
			glfwTerminate();
			return false;
		}
		else
			g_log.write("Window with title '" + title + "' opened");

		// Set the current OpenGL context to this window's context
		glfwMakeContextCurrent(this->window);
		g_log.write("Switched active OpenGL window context");

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
			glfwSetCursorPos(this->window, width / 2, height / 2);

			// Find the amount the cursor has moved since the last reset
			this->inputstate.setCursorOffset(glm::vec2(cursor_x - width / 2, cursor_y - height / 2));
		}
		else
			this->inputstate.setCursorOffset(glm::vec2(0));

		// Update the input state depending on keys
		this->inputstate.setKeyState(InputState::Key::MOVE_UP    , glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS);
		this->inputstate.setKeyState(InputState::Key::MOVE_LEFT  , glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS);
		this->inputstate.setKeyState(InputState::Key::MOVE_DOWN  , glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS);
		this->inputstate.setKeyState(InputState::Key::MOVE_RIGHT , glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS);
		this->inputstate.setKeyState(InputState::Key::MOVE_CROUCH, glfwGetKey(this->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS);
		this->inputstate.setKeyState(InputState::Key::MOVE_JUMP  , glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS);
	}

	void Window::setCursorTrapped(bool trapped)
	{
		this->cursor_trapped = trapped;

		if (this->cursor_trapped)
			glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		else
			glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	void Window::close()
	{
		glfwTerminate();
		g_log.write("Closed window");
	}
}
