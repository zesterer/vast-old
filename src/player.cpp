// Vast
#include <vast/player.hpp>
#include <vast/log.hpp>

namespace Vast
{
	Player::Player(glm::vec3 pos)
	{
		this->state.pos = pos;
	}

	bool Player::event_handler(SceneObject& parent, SceneEvent event)
	{
		switch (event.type)
		{
		case SceneEvent::Type::TICK:
			break;
		default:
			break;
		}

		return Entity::event_handler(parent, event);
	}
}
