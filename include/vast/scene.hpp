#ifndef VAST_SCENE_HPP
#define VAST_SCENE_HPP

// Vast
#include <vast/camera.hpp>
#include <vast/renderer.hpp>
#include <vast/inputstate.hpp>

// Library
#include <glm/glm.hpp>

namespace Vast
{
	class Scene
	{
	private:
		Camera camera;

	public:
		const Camera& getCamera() const { return this->camera; }

		bool init();
		void tick();
		void handleInput(const InputState& inputstate);
		void draw(Renderer& renderer);
	};
}

#endif
