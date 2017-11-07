// Vast
#include <vast/voxelentity.hpp>

namespace Vast
{
	bool VoxelEntity::event_handler(SceneObject& parent, SceneEvent event)
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

		return Entity::event_handler(parent, event);
	}
}
