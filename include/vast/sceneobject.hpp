#ifndef VAST_SCENEOBJ_HPP
#define VAST_SCENEOBJ_HPP

// Vast
#include <vast/state.hpp>

// Library
#include <glm/glm.hpp>

// Standard
#include <vector>
#include <memory>

namespace Vast
{
	class SceneObject
	{
	public:
		StaticState state;

		std::vector<std::weak_ptr<SceneObject>> children;

		virtual void tick_handler(SceneObject& parent) { (void)parent; }
		virtual void update_handler(SceneObject& parent) { (void)parent; }

		void addChild(std::weak_ptr<SceneObject> child)
		{
			this->children.push_back(child);
		}

		void updateChildren()
		{
			for (std::weak_ptr<SceneObject> wref : this->children)
			{
				if (wref.expired())
					continue;

				std::shared_ptr<SceneObject> child = wref.lock();
				child->update(*this);
			}
		}

		void tickChildren()
		{
			for (std::weak_ptr<SceneObject> wref : this->children)
			{
				if (wref.expired())
					continue;

				std::shared_ptr<SceneObject> child = wref.lock();
				child->tick(*this);
			}
		}

		void update(SceneObject& parent)
		{
			this->update_handler(parent);
			this->updateChildren();
		}

		void tick(SceneObject& parent)
		{
			this->tick_handler(parent);
			this->updateChildren();
		}
	};
}

#endif
