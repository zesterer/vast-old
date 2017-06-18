#ifndef VAST_SCENE_HPP
#define VAST_SCENE_HPP

// Vast
#include <vast/heap.hpp>
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
		Heap* heap = nullptr;

		Camera camera;

	public:
		const Camera& getCamera() const { return this->camera; }

		bool init(Heap& heap);
		void tick();
		void handleInput(const InputState& inputstate);
		void draw(Renderer& renderer);
	};
}

#endif
