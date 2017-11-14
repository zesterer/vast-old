// Vast
#include <vast/camera.hpp>

// Library
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

namespace Vast
{
	void Camera::updateMatrices(SceneObject& parent)
	{
		this->state.updateRelativeTo(parent.state.mat);

		this->proj_mat = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.001f, 10000000.0f);

		this->view_mat = glm::mat4(1.0f);

		this->view_mat = glm::rotate(this->view_mat, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0)); // Pitch
		this->view_mat = glm::rotate(this->view_mat, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0)); // Yaw

		this->view_mat = this->view_mat * glm::toMat4(this->state.ori);

		glm::mat4 inv_parent = glm::inverse(parent.state.mat);

		this->view_mat = glm::translate(this->view_mat, -this->state.pos);
		this->view_mat *= inv_parent;

		this->spin_mat = this->view_mat;
		glm::vec3 pinv = glm::vec3(parent.state.mat * glm::vec4(this->state.pos, 1));
		this->spin_mat = glm::translate(this->spin_mat, pinv); // Translate back to camera space
	}

	bool Camera::event_handler(SceneObject& parent, SceneEvent event)
	{
		switch (event.type)
		{
		case SceneEvent::Type::TICK:
			this->state.tick();
			break;

		case SceneEvent::Type::UPDATE:
			this->updateMatrices(parent);
			break;

		default:
			break;
		}

		return SceneObject::event_handler(parent, event);
	}

	glm::vec3 Camera::getLookVector() const
	{
		return glm::normalize(glm::vec3(
			glm::cos(glm::radians(this->state.ori.x)) * glm::cos(glm::radians(this->state.ori.y)), // x
			glm::sin(glm::radians(this->state.ori.x)) * glm::cos(glm::radians(this->state.ori.y)), // y
			-glm::sin(glm::radians(this->state.ori.y)) // z
		));
	}
}
