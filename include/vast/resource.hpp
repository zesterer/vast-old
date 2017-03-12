#ifndef VAST_RESOURCE_HPP
#define VAST_RESOURCE_HPP

namespace Vast
{
	class Heap;

	class Resource
	{
		friend class Heap;
	private:
		unsigned long id;

	protected:
		void setID(unsigned long id) { this->id = id; }

	public:

		unsigned long getID() { return this->id; }
	};
}

#endif
