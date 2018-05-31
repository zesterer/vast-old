// Vast
#include <vast/voxelentity.hpp>
#include <vast/log.hpp>

// Standard
#include <fstream>

namespace Vast
{
	glm::vec3 voxel_colors[] = {
		glm::vec3(0, 0, 0),       // 0
		glm::vec3(1, 1, 1),       // 1
		glm::vec3(1, 0.7, 0.7),   // 2
		glm::vec3(0.7, 1, 0.7),   // 3
		glm::vec3(0.7, 0.7, 1),   // 4
		glm::vec3(1, 1, 0.7),     // 5
		glm::vec3(0.2, 0.2, 0.2), // 6
	};

	VoxelEntity::VoxelEntity(glm::ivec3 size, glm::vec3 center) : vol(size), center(center)
	{
		for (int i = 0; i < this->vol.size().x; i ++)
			for (int j = 0; j < this->vol.size().y; j ++)
				for (int k = 0; k < this->vol.size().z; k ++)
					if (800 + rand() % 200 > glm::length(glm::vec3(i, j, k) - center) * (2000 / size.x))
						this->vol.set(glm::ivec3(i, j, k), 1);
					else
						this->vol.set(glm::ivec3(i, j, k), 0);
	}

	VoxelEntity::VoxelEntity(std::string filename)
	{
		std::ifstream file(filename);
		if (file.is_open())
		{
			int sx, sy, sz;
			file >> sx;
			file >> sy;
			file >> sz;

			this->vol.set_size(glm::ivec3(sx, sy, sz));

			float offx, offy, offz;
			file >> offx;
			file >> offy;
			file >> offz;

			this->center = glm::vec3(offx, offy, offz);

			for (size_t i = 0; !file.eof() && i < (size_t)(sx * sy * sz); i ++)
			{
				int v;
				file >> v;

				this->vol.set(glm::ivec3((i / (sy * sz)) % sx, (i / sz) % sy, i % sz), v);
			}

			file.close();
		}

		this->remesh();
	}

	bool VoxelEntity::event_handler(SceneObject& parent, SceneEvent event)
	{
		switch (event.type)
		{
		default:
			break;
		}

		return Entity::event_handler(parent, event);
	}

	void VoxelEntity::remesh()
	{
		Mesh mesh;

		for (int i = 0; i < this->vol.size().x; i ++)
			for (int j = 0; j < this->vol.size().y; j ++)
				for (int k = 0; k < this->vol.size().z; k ++)
				{
					int vox = this->vol.get(glm::ivec3(i, j, k));

					if (vox == 0)
						continue;

					// Top
					if (this->vol.get(glm::ivec3(i, j, k + 1)) == 0)
						mesh.add(Quad(
							glm::vec3(i, j, k + 1),
							glm::vec3(i + 1, j, k + 1),
							glm::vec3(i + 1, j + 1, k + 1),
							glm::vec3(i, j + 1, k + 1),
							voxel_colors[vox], // Color
							glm::vec3(0, 0, 1), // Normal
							glm::vec2(0, 0), // UV
							glm::vec2(0, 1),
							glm::vec2(1, 1),
							glm::vec2(1, 0)
						));

					// Bottom
					if (this->vol.get(glm::ivec3(i, j, k - 1)) == 0)
						mesh.add(Quad(
							glm::vec3(i, j, k),
							glm::vec3(i , j + 1, k),
							glm::vec3(i + 1, j + 1, k),
							glm::vec3(i + 1, j, k),
							voxel_colors[vox], // Color
							glm::vec3(0, 0, -1), // Normal
							glm::vec2(0, 0), // UV
							glm::vec2(0, 1),
							glm::vec2(1, 1),
							glm::vec2(1, 0)
						));

					// Front
					if (this->vol.get(glm::ivec3(i + 1, j, k)) == 0)
						mesh.add(Quad(
							glm::vec3(i + 1, j, k),
							glm::vec3(i + 1, j + 1, k),
							glm::vec3(i + 1, j + 1, k + 1),
							glm::vec3(i + 1, j, k + 1),
							voxel_colors[vox], // Color
							glm::vec3(1, 0, 0), // Normal
							glm::vec2(0, 0), // UV
							glm::vec2(0, 1),
							glm::vec2(1, 1),
							glm::vec2(1, 0)
						));

					// Back
					if (this->vol.get(glm::ivec3(i - 1, j, k)) == 0)
						mesh.add(Quad(
							glm::vec3(i, j, k),
							glm::vec3(i, j, k + 1),
							glm::vec3(i, j + 1, k + 1),
							glm::vec3(i, j + 1, k),
							voxel_colors[vox], // Color
							glm::vec3(-1, 0, 0), // Normal
							glm::vec2(0, 0), // UV
							glm::vec2(0, 1),
							glm::vec2(1, 1),
							glm::vec2(1, 0)
						));

					// Right
					if (this->vol.get(glm::ivec3(i, j + 1, k)) == 0)
						mesh.add(Quad(
							glm::vec3(i, j + 1, k),
							glm::vec3(i, j + 1, k + 1),
							glm::vec3(i + 1, j + 1, k + 1),
							glm::vec3(i + 1, j + 1, k),
							voxel_colors[vox], // Color
							glm::vec3(0, 1, 0), // Normal
							glm::vec2(0, 0), // UV
							glm::vec2(0, 1),
							glm::vec2(1, 1),
							glm::vec2(1, 0)
						));

					// Left
					if (this->vol.get(glm::ivec3(i, j - 1, k)) == 0)
						mesh.add(Quad(
							glm::vec3(i, j, k),
							glm::vec3(i + 1, j, k),
							glm::vec3(i + 1, j, k + 1),
							glm::vec3(i, j, k + 1),
							voxel_colors[vox], // Color
							glm::vec3(0, 1, 0), // Normal
							glm::vec2(0, 0), // UV
							glm::vec2(0, 1),
							glm::vec2(1, 1),
							glm::vec2(1, 0)
						));
				}

		mesh.offset(-this->center);

		this->setModel(std::make_shared<Model>(mesh));
	}

	bool VoxelEntity::doesCollide(glm::vec3 pos, glm::vec3 sz)
	{
		for (float i = pos.x; i <= pos.x + sz.x; i += 0.1f)
			for (float j = pos.y; j <= pos.y + sz.y; j += 0.1f)
				for (float k = pos.z; k <= pos.z + sz.z; k += 0.1f)
				{
					if (this->vol.get(glm::ivec3(
						i + this->center.x - sz.x / 2,
						j + this->center.y - sz.y / 2,
						k + this->center.z - sz.z / 2
					)) != 0)
						return true;
				}
		return false;
	}

	glm::vec3 VoxelEntity::tryCollide(glm::vec3 pos, glm::vec3 tpos, glm::vec3 sz)
	{
		glm::vec3 offs[3] = {
			glm::vec3(0, 0, 1),
			glm::vec3(0, 1, 0),
			glm::vec3(1, 0, 0),
		};
		
		glm::vec3 diff = tpos - pos;
		for (size_t j = 0; j < 100; j ++)
			for (size_t i = 0; i < 3; i ++)
				if (!this->doesCollide(pos + diff * offs[i] * 0.01f, sz))
					pos += diff * offs[i] * 0.01f;
		
		return pos;
	}
}
