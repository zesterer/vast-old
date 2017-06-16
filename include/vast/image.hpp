#ifndef VAST_IMAGE_HPP
#define VAST_IMAGE_HPP

// Library
#include <glm/glm.hpp>

// Standard
#include <string>

namespace Vast
{
	class Image
	{
	private:
		unsigned char* data = nullptr;
		bool loaded = false;
		glm::ivec2 size;

	public:
		bool getLoaded() const { return this->loaded; }
		glm::ivec2 getSize() const { return this->size; }
		const unsigned char* getData() const { return this->data; }

		Image(std::string filename) { this->load(filename); }
		~Image();
		void unload();
		bool load(std::string filename);
	};
}

#endif
