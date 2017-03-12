#ifndef VAST_SHADER_HPP
#define VAST_SHADER_HPP

// Library
#include <glbinding/gl/types.h>

// Standard
#include <string>

namespace Vast
{
	class Shader
	{
	private:
		gl::GLuint vert_shader_id;
		gl::GLuint frag_shader_id;
		gl::GLuint program_id;

	public:
		gl::GLuint getProgramID() const { return this->program_id; }
		gl::GLuint getUniformID(std::string identifier) const;

		bool loadFiles(std::string vert_filename, std::string frag_filename);
		bool loadStrings(std::string vert_shader_code, std::string frag_shader_code);
	};
}

#endif
