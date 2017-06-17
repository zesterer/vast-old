#ifndef VAST_CAMERA_HPP
#define VAST_CAMERA_HPP

// Vast
//#include <vast/entity.hpp>

// Library
#include <glm/glm.hpp>

namespace Vast
{
	class Scene;

	class Camera
	{
	public:
		glm::vec3 pos;
		glm::vec3 rot;
		glm::vec3 scale = glm::vec3(1, 1, 1);

	private:
		glm::mat4 proj_mat;
		glm::mat4 view_mat;

	public:
		glm::vec3 getPosition() const { return this->pos; }

		glm::mat4 getProjMatrix() const { return this->proj_mat; }
		glm::mat4 getViewMatrix() const { return this->view_mat; }

		glm::vec3 getLookVector() const;

		void tick(Scene& scene);
	};
}

#endif
