#ifndef VAST_TEXTURE_HPP
#define VAST_TEXTURE_HPP

// Vast
#include <vast/image.hpp>

// Library
#include <glbinding/gl/types.h>
#include <glm/glm.hpp>

namespace Vast
{
	class Texture
	{
	private:
		gl::GLuint texture_id;
		bool initiated = false;
		bool buffered = false;
		gl::GLenum format;
		glm::ivec2 size;

	public:
		gl::GLuint getTextureID() const { return this->texture_id; }
		bool getBuffered() const { return this->buffered; }
		gl::GLenum getFormat() const { return this->format; }
		glm::ivec2 getSize() const { return this->size; }

		~Texture();
		bool init();
		void unload();
		bool load(const gl::GLvoid* data, glm::ivec2 size, gl::GLenum format);
		bool load(const Image& image);
	};
}

#endif
