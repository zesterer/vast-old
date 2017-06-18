#ifndef VAST_MODEL_HPP
#define VAST_MODEL_HPP

// Vast
#include <vast/resource.hpp>
#include <vast/mesh.hpp>

// Library
#include <glbinding/gl/types.h>

namespace Vast
{
	class Model : public Resource
	{
	private:
		gl::GLuint vert_buff_id;
		gl::GLuint vert_arr_id;
		unsigned long vert_count;
		bool initiated = false;
		bool buffered = false;
		VertexFormat vert_format;

	public:
		gl::GLuint getVertexBufferID() const { return this->vert_buff_id; }
		gl::GLuint getVertexArrayID() const { return this->vert_arr_id; }
		unsigned long getVertexCount() const { return this->vert_count; }
		VertexFormat getVertexFormat() { return this->vert_format; }
		bool getBuffered() { return this->buffered; }

		Model() {}
		Model(const Mesh& mesh) { this->load(mesh); }
		~Model();
		bool init();
		void unload();
		bool load(const gl::GLfloat* vertices, size_t vert_size, unsigned long vert_count, VertexFormat vert_format);
		bool load(const Mesh& mesh);
	};
}

#endif
