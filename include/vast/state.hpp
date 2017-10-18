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

		void updateRelativeTo(glm::mat4 mat)
		{
			glm::normalize(this->ori); // Normalize quaternions

			this->mat = glm::translate(mat, this->pos); // Position
			this->mat *= glm::toMat4(this->ori);        // Orientation
		}

		void update()
		{
			this->updateRelativeTo(glm::mat4(1));
		}
	};

	struct DynamicState
	{
		glm::vec3 vel;
		glm::quat rot = glm::quat(glm::vec3(0.0, 0.0, 0.01));

		void tick(StaticState& state)
		{
			glm::normalize(this->rot); // Normalize quaternions

			state.pos += this->vel;            // Velocity
			state.ori = this->rot * state.ori; // Rotation
		}
	};
}

#endif
