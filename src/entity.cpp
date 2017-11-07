// Vast
#include <vast/entity.hpp>

namespace Vast
{
	bool Entity::event_handler(SceneObject& parent, SceneEvent event)
	{
		switch (event.type)
		{
		case SceneEvent::Type::TICK:
			this->state.tick();
			break;

		case SceneEvent::Type::UPDATE:
			this->state.updateRelativeTo(parent.state.mat);
			break;

		default:
			break;
		}

		return SceneObject::event_handler(parent, event);
	}
}
