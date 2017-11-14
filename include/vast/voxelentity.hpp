#ifndef VAST_VOXELENTITY_HPP
#define VAST_VOXELENTITY_HPP

// Vast
#include <vast/entity.hpp>
#include <vast/volume.hpp>

namespace Vast
{
	class VoxelEntity : public Entity
	{
	private:
		Volume vol;
		glm::vec3 center;

	protected:
		bool event_handler(SceneObject& parent, SceneEvent event) override;

	public:
		VoxelEntity(glm::ivec3 size, glm::vec3 center);
		VoxelEntity(std::string filename);
		void remesh();

		glm::vec3 tryCollide(glm::vec3 pos, glm::vec3 sz);
	};
}

#endif
