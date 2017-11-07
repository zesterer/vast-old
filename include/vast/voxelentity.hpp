#ifndef VAST_VOXELENTITY_HPP
#define VAST_VOXELENTITY_HPP

// Vast
#include <vast/entity.hpp>

namespace Vast
{
	class VoxelEntity : public Entity
	{
	protected:
		bool event_handler(SceneObject& parent, SceneEvent event) override;

	public:
		// Nothing yet
	};
}

#endif
