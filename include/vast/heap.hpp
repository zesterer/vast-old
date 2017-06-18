#ifndef VAST_HEAP_HPP
#define VAST_HEAP_HPP

// Vast
#include <vast/resource.hpp>

// Standard
#include <map>
#include <memory>

namespace Vast
{
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
		rid create(Args ... args)
		{
			std::shared_ptr<T> ptr(new T(args ...));
			rid id = this->generateID();
			ptr->setID(id);
			this->items[id] = ptr;
			return id;
		}

		template <typename T, typename ... Args>
		std::shared_ptr<T> get(rid id)
		{
			return this->items[id];
		}

		bool contains(rid id)
		{
			return this->items.find(id) != this->items.end();
		}
	};
}

#endif
