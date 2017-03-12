#ifndef VAST_INPUTSTATE_HPP
#define VAST_INPUTSTATE_HPP

// Library
#include <glm/glm.hpp>

namespace Vast
{
	class Window;

	class InputState
	{
		friend class Window;
	private:
		bool key_states[6];
		glm::vec2 cursor_offset;

	public:
		enum class Key : int
		{
			MOVE_UP = 0,
			MOVE_LEFT = 1,
			MOVE_DOWN = 2,
			MOVE_RIGHT = 3,
			MOVE_CROUCH = 4,
			MOVE_JUMP = 5,
		};

	protected:
		void setKeyState(Key key, bool state) { this->key_states[(int)key] = state; }
		void setCursorOffset(glm::vec2 cursor_offset) { this->cursor_offset = cursor_offset; }

	public:
		bool getKeyState(Key key) const { return this->key_states[(int)key]; }
		glm::vec2 getCursorOffset() const { return this->cursor_offset; }
	};
}

#endif
