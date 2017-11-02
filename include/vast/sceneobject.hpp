#ifndef VAST_SCENEOBJ_HPP
#define VAST_SCENEOBJ_HPP

// Vast
#include <vast/sceneevent.hpp>
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

		virtual bool event_handler(SceneObject& parent, SceneEvent event) { (void)parent; (void)event; return false; }

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
				if (!child->event_handler(*this, event)) // Only propagate event if not cancelled
					child->eventChildren(event);
			}
		}
	};
}

#endif
