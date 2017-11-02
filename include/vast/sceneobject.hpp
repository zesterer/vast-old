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
	struct SceneEvent
	{
		enum class Type
		{
			UPDATE,
			TICK,
		};

		Type type;
		bool cancelled = false;

		SceneEvent(Type type) : type(type) {}
	};

	class SceneObject
	{
	public:
		StaticState state;

		std::vector<std::weak_ptr<SceneObject>> children;

		virtual void event_handler(SceneObject& parent, SceneEvent event) { (void)parent; (void)event; }

		void addChild(std::weak_ptr<SceneObject> child)
		{
			this->children.push_back(child);
		}

		void eventChildren(SceneEvent event)
		{
			for (std::weak_ptr<SceneObject> wref : this->children)
			{
				if (wref.expired())
					continue;

				std::shared_ptr<SceneObject> child = wref.lock();
				child->event_handler(*this, event);
				child->eventChildren(event);
			}
		}
	};
}

#endif
