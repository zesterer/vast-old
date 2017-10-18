// Vast
#include <vast/camera.hpp>

// Library
#include <glm/gtc/matrix_transform.hpp>

namespace Vast
{
	void Camera::tick_handler(SceneObject& parent)
	{
		(void)parent;
	}

	void Camera::update_handler(SceneObject& parent)
	{
		this->state.updateRelativeTo(parent.state.mat);

		this->proj_mat = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 10000000.0f);

		this->view_mat = glm::mat4(1.0f);

		this->view_mat = glm::rotate(this->view_mat, glm::radians(this->state.ori.z), glm::vec3(0.0, 0.0, 1.0)); // Roll
		this->view_mat = glm::rotate(this->view_mat, glm::radians(-90.0f + this->state.ori.y), glm::vec3(1.0, 0.0, 0.0)); // Pitch
		this->view_mat = glm::rotate(this->view_mat, glm::radians(90.0f - this->state.ori.x), glm::vec3(0.0, 0.0, 1.0)); // Yaw

		glm::mat4 inv_parent = glm::inverse(parent.state.mat);

		this->spin_mat = this->view_mat * inv_parent;
		this->view_mat = glm::translate(this->view_mat, -this->state.pos);
		this->view_mat *= inv_parent;
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
