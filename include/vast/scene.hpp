#ifndef VAST_SCENE_HPP
#define VAST_SCENE_HPP

// Vast
#include <vast/camera.hpp>
#include <vast/renderer.hpp>
#include <vast/inputstate.hpp>
#include <vast/entity.hpp>

// Library
#include <glm/glm.hpp>

// Standard
#include <vector>
#include <memory>

namespace Vast
{
	class Scene
	{
	private:
		Camera camera;
		std::vector<std::shared_ptr<Entity>> entities;

	public:
		const Camera& getCamera() const { return this->camera; }

		bool init();
		void tick();
		void handleInput(const InputState& inputstate);
		void draw(Renderer& renderer);
		void drawEntity(Renderer& renderer, const Entity& entity);
	};
}

#endif
