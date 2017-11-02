#ifndef VAST_SCENEEVENT_HPP
#define VAST_SCENEEVENT_HPP

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
}

#endif
