#ifndef VAST_PLAYER_HPP
#define VAST_PLAYER_HPP

// Vast
#include <vast/entity.hpp>
#include <vast/inputstate.hpp>

namespace Vast
{
	class Player : public Entity
	{
	private:
		float yaw, pitch;

	protected:
		bool event_handler(SceneObject& parent, SceneEvent event) override;

	public:
		Player(glm::vec3 pos);
		void processInputs(InputState& inputstate);
	};
}

#endif
