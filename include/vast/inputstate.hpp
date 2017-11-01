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

	public:
		enum class Key : int
		{
			MOVE_UP        = 0,
			MOVE_LEFT      = 1,
			MOVE_DOWN      = 2,
			MOVE_RIGHT     = 3,

			MOVE_CROUCH    = 4,
			MOVE_JUMP      = 5,

			MOVE_SFORWARD  = 6,
			MOVE_SLEFT     = 7,
			MOVE_SBACKWARD = 8,
			MOVE_SRIGHT    = 9,
			MOVE_SCW       = 10,
			MOVE_SCCW      = 11,

			MAX = 12,
		};

	private:
		bool key_states[(size_t)Key::MAX];
		glm::vec2 cursor_offset;

	protected:
		void setKeyState(Key key, bool state) { this->key_states[(int)key] = state; }
		void setCursorOffset(glm::vec2 cursor_offset) { this->cursor_offset = cursor_offset; }

	public:
		bool getKeyState(Key key) const { return this->key_states[(int)key]; }
		glm::vec2 getCursorOffset() const { return this->cursor_offset; }
	};
}

#endif
