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
		std::map<unsigned long, std::shared_ptr<Resource>> items;
		unsigned long id_counter = 0;

		unsigned long generateID()
		{
			this->id_counter ++;
			return this->id_counter;
		}

	public:
		template <typename T, typename ... Args>
		std::shared_ptr<T> create(Args ... args)
		{
			std::shared_ptr<T> ptr(new T(args ...));
			this->items[this->generateID()] = ptr;
			return ptr;
		}

		template <typename T, typename ... Args>
		std::shared_ptr<T> get(unsigned long id)
		{
			return this->items[id];
		}

		bool contains(unsigned long id)
		{
			return this->items.find(id) != this->items.end();
		}
	};
}

#endif
