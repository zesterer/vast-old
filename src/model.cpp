// Vast
#include <vast/model.hpp>
#include <vast/log.hpp>

// Library
#include <glbinding/gl/gl.h>

namespace Vast
{
	Model::~Model()
	{
		this->unload();
	}

	bool Model::init()
	{
		if (this->initiated)
			return false;

		// Generate a vertex array and a buffer for this model
		gl::glGenVertexArrays(1, &this->vert_arr_id);
		gl::glGenBuffers(1, &this->vert_buff_id);

		g_log.write("Generated new vertex array");

		this->initiated = true;
		return true;
	}

	void Model::unload()
	{
		if (this->initiated)
		{
			gl::glDeleteBuffers(1, &this->vert_buff_id);
			gl::glDeleteVertexArrays(1, &this->vert_arr_id);
		}

		this->buffered = false;
		this->initiated = false;
	}

	bool Model::load(const gl::GLfloat* vertices, size_t vert_size, unsigned long vert_count, VertexFormat vert_format)
	{
		this->init();

		this->vert_format = vert_format;
		this->vert_count = vert_count;

		// Bind the model vertex array
		gl::glBindVertexArray(this->vert_arr_id);

		// Buffer vertex data into the vertex buffer
		gl::glBindBuffer(gl::GL_ARRAY_BUFFER, this->vert_buff_id);
		gl::glBufferData(gl::GL_ARRAY_BUFFER, vert_size * vert_count, vertices, gl::GL_STATIC_DRAW);

		g_log.write("Buffered vertex data of size '" + std::to_string(vert_size * vert_count) + "' containing '" + std::to_string(vert_count) + "' vertices");

		// Set vertex attributes for the vertex data (position, color, normal, etc.)
		switch (this->vert_format)
		{
		case VertexFormat::POS_COL_UV_NORM:
			{
				gl::glEnableVertexAttribArray(0); // Position
				gl::glVertexAttribPointer(0, 3, gl::GL_FLOAT, gl::GL_FALSE, vert_size, (void*)0);
				gl::glEnableVertexAttribArray(1); // Color
				gl::glVertexAttribPointer(1, 3, gl::GL_FLOAT, gl::GL_FALSE, vert_size, (void*)(sizeof(gl::GLfloat) * 3));
				gl::glEnableVertexAttribArray(2); // Normal
				gl::glVertexAttribPointer(2, 3, gl::GL_FLOAT, gl::GL_TRUE, vert_size, (void*)(sizeof(gl::GLfloat) * 6));
				gl::glEnableVertexAttribArray(3); // UV
				gl::glVertexAttribPointer(3, 2, gl::GL_FLOAT, gl::GL_FALSE, vert_size, (void*)(sizeof(gl::GLfloat) * 9));
			}
			break;

		default:
		case VertexFormat::POS_COL_NORM:
			{
				gl::glEnableVertexAttribArray(0); // Position
				gl::glVertexAttribPointer(0, 3, gl::GL_FLOAT, gl::GL_FALSE, vert_size, (void*)0);
				gl::glEnableVertexAttribArray(1); // Color
				gl::glVertexAttribPointer(1, 3, gl::GL_FLOAT, gl::GL_FALSE, vert_size, (void*)(sizeof(gl::GLfloat) * 3));
				gl::glEnableVertexAttribArray(2); // Normal
				gl::glVertexAttribPointer(2, 3, gl::GL_FLOAT, gl::GL_TRUE, vert_size, (void*)(sizeof(gl::GLfloat) * 6));
			}
			break;
		}

		this->buffered = true;

		return true;
	}

	bool Model::load(const Mesh& mesh)
	{
		return this->load((const gl::GLfloat*)&mesh.getVertexArray()[0], sizeof(Vertex), mesh.getVertexCount(), VertexFormat::POS_COL_UV_NORM);
	}
}
