// Vast
#include <vast/camera.hpp>

// Library
#include <glm/gtc/matrix_transform.hpp>

namespace Vast
{
	void Camera::tick(Scene& scene)
	{
		this->proj_mat = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 10000000.0f);

		this->view_mat = glm::mat4(1.0f);//glm::lookAt(this->pos, glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));

		this->view_mat = glm::rotate(this->view_mat, glm::radians(this->rot.z), glm::vec3(0.0, 0.0, 1.0)); // Roll
		this->view_mat = glm::rotate(this->view_mat, glm::radians(-90.0f + this->rot.y), glm::vec3(1.0, 0.0, 0.0)); // Pitch
		this->view_mat = glm::rotate(this->view_mat, glm::radians(90.0f - this->rot.x), glm::vec3(0.0, 0.0, 1.0)); // Yaw

		this->spin_mat = this->view_mat;

		this->view_mat = glm::translate(this->view_mat, -this->pos);
	}

	glm::vec3 Camera::getLookVector() const
	{
		return glm::normalize(glm::vec3(
			glm::cos(glm::radians(this->rot.x)) * glm::cos(glm::radians(this->rot.y)), // x
			glm::sin(glm::radians(this->rot.x)) * glm::cos(glm::radians(this->rot.y)), // y
			-glm::sin(glm::radians(this->rot.y)) // z
		));
	}
}
