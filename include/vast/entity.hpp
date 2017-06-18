#ifndef VAST_ENTITY_HPP
#define VAST_ENTITY_HPP

// Vast
#include <vast/state.hpp>
#include <vast/heap.hpp>

namespace Vast
{
	class Entity : public Resource
	{
	private:
		DynamicState state;

		rid model;
		rid shader;
		rid texture;

	public:
	};
}

#endif
