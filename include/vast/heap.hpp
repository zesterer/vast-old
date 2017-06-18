#ifndef VAST_HEAP_HPP
#define VAST_HEAP_HPP

// Vast
#include <vast/resource.hpp>

// Standard
#include <map>
#include <memory>

namespace Vast
{
	template <typename T>
	struct ResourcePair
	{
		rid id;
		std::shared_ptr<T> ptr;

		ResourcePair(rid id, std::shared_ptr<T> ptr)
		{
			this->id = id;
			this->ptr = ptr;
		}
	};

	class Heap
	{
	private:
		std::map<rid, std::shared_ptr<Resource>> items;
		rid id_counter = 0;

		rid generateID()
		{
			return ++this->id_counter;
		}

	public:
		template <typename T, typename ... Args>
		std::shared_ptr<T> create(Args ... args)
		{
			std::shared_ptr<T> ptr = std::make_shared<T>(args ...);
			rid id = this->generateID();
			ptr->setID(id);
			this->items[id] = ptr;
			return ptr;
		}

		template <typename T, typename ... Args>
		std::shared_ptr<T> get(rid id)
		{
			return std::static_pointer_cast<T>(this->items[id]);
		}

		bool contains(rid id)
		{
			return this->items.find(id) != this->items.end();
		}
	};

	extern Heap g_heap;
}

#endif
