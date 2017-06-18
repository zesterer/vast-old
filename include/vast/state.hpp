#ifndef VAST_STATE_HPP
#define VAST_STATE_HPP

// Library
#include <glm/glm.hpp>
#include "glm/gtx/quaternion.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Vast
{
	struct StaticState
	{
		glm::vec3 pos;
		glm::quat ori;

		glm::mat4 mat;

		void update()
		{
			glm::normalize(this->ori); // Normalize quaternions

			this->mat = glm::translate(glm::mat4(1), this->pos); // Position
			this->mat *= glm::toMat4(this->ori);                 // Orientation
		}
	};

	struct DynamicState : public StaticState
	{
		glm::vec3 vel;
		glm::quat rot = glm::quat(glm::vec3(0.0, 0.0, 0.01));

		void tick()
		{
			glm::normalize(this->rot); // Normalize quaternions

			this->pos += this->vel;            // Velocity
			this->ori = this->rot * this->ori; // Rotation

			this->update();
		}
	};
}

#endif
