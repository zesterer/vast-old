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

		glm::vec3 vel;
		glm::quat rot;

		glm::mat4 mat;

		void updateRelativeTo(glm::mat4 mat)
		{
			this->mat = glm::translate(mat, this->pos); // Position
			this->mat *= glm::toMat4(this->ori);        // Orientation
		}

		void update()
		{
			this->updateRelativeTo(glm::mat4(1));
		}

		void tick()
		{
			this->pos += this->vel;            // Velocity
			this->ori = this->rot * this->ori; // Rotation

			glm::normalize(this->rot);
			glm::normalize(this->ori);
		}
	};
}

#endif
