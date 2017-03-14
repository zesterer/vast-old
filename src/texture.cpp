// Vast
#include <vast/texture.hpp>
#include <vast/log.hpp>

// Library
#include <glbinding/gl/gl.h>

namespace Vast
{
	Texture::~Texture()
	{
		this->unload();
	}

	bool Texture::init()
	{
		if (this->initiated)
			return false;

		// Generate a texture
		gl::glGenTextures(1, &this->texture_id);

		g_log.write("Generated new texture");

		this->initiated = true;
		return true;
	}

	void Texture::unload()
	{
		if (this->initiated)
			gl::glDeleteTextures(1, &this->texture_id);

		this->buffered = false;
		this->initiated = false;
	}

	bool Texture::load(const gl::GLvoid* data, glm::ivec2 size, gl::GLenum format)
	{
		this->init();

		this->size = size;
		this->format = format;

		// Bind the model vertex array
		gl::glBindTexture(gl::GL_TEXTURE_2D, this->texture_id);

		// Buffer pixel data into the texture
		gl::glTexImage2D(gl::GL_TEXTURE_2D, 0, (gl::GLint)gl::GL_RGB, this->size.x, this->size.y, 0, this->format, gl::GL_UNSIGNED_BYTE, data);

		// Set texture parameters
		gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MAG_FILTER, (gl::GLuint)gl::GL_LINEAR);
		gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MIN_FILTER, (gl::GLuint)gl::GL_LINEAR);

		g_log.write("Buffered texture of size " + std::to_string(this->size.x) + " x " + std::to_string(this->size.x));

		this->buffered = true;

		return true;
	}

	bool Texture::load(const Image& image)
	{
		return this->load(image.getData(), image.getSize(), gl::GL_RGB);
	}
}
