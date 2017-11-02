#ifndef VAST_CAMERA_HPP
#define VAST_CAMERA_HPP

// Vast
#include <vast/resource.hpp>
#include <vast/sceneobject.hpp>

// Library
#include <glm/glm.hpp>

namespace Vast
{
	class Scene;

	class Camera : public Resource, public SceneObject
	{
	private:
		glm::mat4 proj_mat;
		glm::mat4 view_mat;
		glm::mat4 spin_mat;

	protected:
		void event_handler(SceneObject& parent, SceneEvent event) override;

	public:
		glm::mat4 getProjMatrix() const { return this->proj_mat; }
		glm::mat4 getViewMatrix() const { return this->view_mat; }
		glm::mat4 getSpinMatrix() const { return this->spin_mat; }

		glm::vec3 getLookVector() const;

		void updateMatrices(SceneObject& parent);
	};
}

#endif
