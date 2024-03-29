#ifndef VAST_CUBEMAP_HPP
#define VAST_CUBEMAP_HPP

// Vast
#include <vast/resource.hpp>
#include <vast/image.hpp>

// Library
#include <glbinding/gl/types.h>
#include <glm/glm.hpp>

namespace Vast
{
	class CubeMap : public Resource
	{
	private:
		gl::GLuint cubemap_id;
		bool initiated = false;
		bool buffered = false;
		gl::GLenum format;

	public:
		gl::GLuint getCubeMapID() const { return this->cubemap_id; }
		bool getBuffered() const { return this->buffered; }
		gl::GLenum getFormat() const { return this->format; }

		CubeMap() {}
		CubeMap(
			const Image& image_x_pos,
			const Image& image_x_neg,
			const Image& image_y_pos,
			const Image& image_y_neg,
			const Image& image_z_pos,
			const Image& image_z_neg
		)
		{
			this->load(
				image_x_pos,
				image_x_neg,
				image_y_pos,
				image_y_neg,
				image_z_pos,
				image_z_neg
			);
		}
		~CubeMap();
		bool init();
		void unload();
		bool load(
			const Image& image_x_pos,
			const Image& image_x_neg,
			const Image& image_y_pos,
			const Image& image_y_neg,
			const Image& image_z_pos,
			const Image& image_z_neg
		);
	};
}

#endif
