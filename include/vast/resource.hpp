#ifndef VAST_RESOURCE_HPP
#define VAST_RESOURCE_HPP

namespace Vast
{
	typedef unsigned long rid;

	class Heap;

	class Resource
	{
		friend class Heap;
	private:
		rid id;

	protected:
		void setID(rid id) { this->id = id; }

	public:

		rid getID() { return this->id; }
	};
}

#endif
