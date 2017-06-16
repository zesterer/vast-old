// Vast
#include <vast/cubemap.hpp>
#include <vast/log.hpp>

// Library
#include <glbinding/gl/gl.h>

namespace Vast
{
	CubeMap::~CubeMap()
	{
		this->unload();
	}

	bool CubeMap::init()
	{
		if (this->initiated)
			return false;

		// Generate a texture
		gl::glGenTextures(1, &this->cubemap_id);

		g_log.write("Generated new cubemap");

		this->initiated = true;
		return true;
	}

	void CubeMap::unload()
	{
		if (this->initiated)
			gl::glDeleteTextures(1, &this->cubemap_id);

		this->buffered = false;
		this->initiated = false;
	}

	bool CubeMap::load(
		const Image& image_x_pos,
		const Image& image_x_neg,
		const Image& image_y_pos,
		const Image& image_y_neg,
		const Image& image_z_pos,
		const Image& image_z_neg
	)
	{
		this->init();

		this->format = gl::GL_RGB;

		// Bind the model vertex array
		gl::glBindTexture(gl::GL_TEXTURE_2D, this->cubemap_id);

		// Buffer pixel data into the texture
		gl::glTexImage2D(gl::GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, (gl::GLint)gl::GL_RGB, image_x_pos.getSize().x, image_x_pos.getSize().y, 0, this->format, gl::GL_UNSIGNED_BYTE, image_x_pos.getData());
		gl::glTexImage2D(gl::GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, (gl::GLint)gl::GL_RGB, image_x_neg.getSize().x, image_x_neg.getSize().y, 0, this->format, gl::GL_UNSIGNED_BYTE, image_x_neg.getData());
		gl::glTexImage2D(gl::GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, (gl::GLint)gl::GL_RGB, image_y_pos.getSize().x, image_y_pos.getSize().y, 0, this->format, gl::GL_UNSIGNED_BYTE, image_y_pos.getData());
		gl::glTexImage2D(gl::GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, (gl::GLint)gl::GL_RGB, image_y_neg.getSize().x, image_y_neg.getSize().y, 0, this->format, gl::GL_UNSIGNED_BYTE, image_y_neg.getData());
		gl::glTexImage2D(gl::GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, (gl::GLint)gl::GL_RGB, image_z_pos.getSize().x, image_z_pos.getSize().y, 0, this->format, gl::GL_UNSIGNED_BYTE, image_z_pos.getData());
		gl::glTexImage2D(gl::GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, (gl::GLint)gl::GL_RGB, image_z_neg.getSize().x, image_z_neg.getSize().y, 0, this->format, gl::GL_UNSIGNED_BYTE, image_z_neg.getData());

		gl::glTexParameteri(gl::GL_TEXTURE_CUBE_MAP, gl::GL_TEXTURE_MAG_FILTER, (gl::GLuint)gl::GL_LINEAR);
		gl::glTexParameteri(gl::GL_TEXTURE_CUBE_MAP, gl::GL_TEXTURE_MIN_FILTER, (gl::GLuint)gl::GL_LINEAR);
		gl::glTexParameteri(gl::GL_TEXTURE_CUBE_MAP, gl::GL_TEXTURE_WRAP_S, (gl::GLuint)gl::GL_CLAMP_TO_EDGE);
		gl::glTexParameteri(gl::GL_TEXTURE_CUBE_MAP, gl::GL_TEXTURE_WRAP_T, (gl::GLuint)gl::GL_CLAMP_TO_EDGE);
		gl::glTexParameteri(gl::GL_TEXTURE_CUBE_MAP, gl::GL_TEXTURE_WRAP_R, (gl::GLuint)gl::GL_CLAMP_TO_EDGE);

		g_log.write("Buffered cubemap");

		this->buffered = true;

		return true;
	}
}
