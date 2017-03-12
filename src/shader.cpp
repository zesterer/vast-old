// Vast
#include <vast/shader.hpp>
#include <vast/log.hpp>

// Library
#include <glbinding/gl/gl.h>

// Standard
#include <vector>
#include <fstream>

namespace Vast
{
	bool Shader::loadFiles(std::string vert_filename, std::string frag_filename)
	{
		// Get vertex shader code
		std::string vert_shader_code;
		g_log.write("Loading vertex shader '" + vert_filename + "'...");
		std::ifstream vert_shader_stream(vert_filename, std::ios::in);
		if (vert_shader_stream.is_open())
		{
			std::string line;
			while (std::getline(vert_shader_stream, line))
				vert_shader_code += line + "\n";
			vert_shader_stream.close();
		}
		else
		{
			g_log.write("Error : Cannot open '" + vert_filename + "'");
			return false;
		}

		// Get fragment shader code
		std::string frag_shader_code;
		g_log.write("Loading fragment shader '" + frag_filename + "'...");
		std::ifstream frag_shader_stream(frag_filename, std::ios::in);
		if (frag_shader_stream.is_open())
		{
			std::string line;
			while (std::getline(frag_shader_stream, line))
				frag_shader_code += line + "\n";
			frag_shader_stream.close();
		}
		else
		{
			g_log.write("Error : Cannot open '" + frag_filename + "'");
			return false;
		}

		return this->loadStrings(vert_shader_code.c_str(), frag_shader_code.c_str());
	}

	bool Shader::loadStrings(std::string vert_shader_code, std::string frag_shader_code)
	{
		this->vert_shader_id = gl::glCreateShader(gl::GL_VERTEX_SHADER);
		this->frag_shader_id = gl::glCreateShader(gl::GL_FRAGMENT_SHADER);

		gl::GLint result = (gl::GLint)gl::GL_FALSE;
		int info_log_len;

		// Compile vertex shader
		g_log.write("Compiling vertex shader...");
		const char* vert_shader_code_ptr = vert_shader_code.c_str();
		gl::glShaderSource(this->vert_shader_id, 1, &vert_shader_code_ptr, NULL);
		gl::glCompileShader(this->vert_shader_id);

		gl::glGetShaderiv(this->vert_shader_id, gl::GL_COMPILE_STATUS, &result);
		gl::glGetShaderiv(this->vert_shader_id, gl::GL_INFO_LOG_LENGTH, &info_log_len);
		if (info_log_len > 1)
		{
			std::vector<char> shader_error_msg(info_log_len + 1);
			gl::glGetShaderInfoLog(this->vert_shader_id, info_log_len, NULL, &shader_error_msg[0]);
			g_log.write(std::string("Error : ") + &shader_error_msg[0]);
			return false;
		}

		// Compile fragment shader
		g_log.write("Compiling fragment shader...");
		const char* frag_shader_code_ptr = frag_shader_code.c_str();
		gl::glShaderSource(this->frag_shader_id, 1, &frag_shader_code_ptr, NULL);
		gl::glCompileShader(this->frag_shader_id);

		gl::glGetShaderiv(this->frag_shader_id, gl::GL_COMPILE_STATUS, &result);
		gl::glGetShaderiv(this->frag_shader_id, gl::GL_INFO_LOG_LENGTH, &info_log_len);
		if (info_log_len > 1)
		{
			std::vector<char> shader_error_msg(info_log_len + 1);
			gl::glGetShaderInfoLog(this->frag_shader_id, info_log_len, NULL, &shader_error_msg[0]);
			g_log.write(std::string("Error : ") + &shader_error_msg[0]);
			return false;
		}

		g_log.write("Linking shader program...");
		this->program_id = gl::glCreateProgram();
		gl::glAttachShader(this->program_id, this->vert_shader_id);
		gl::glAttachShader(this->program_id, this->frag_shader_id);
		gl::glLinkProgram(this->program_id);

		return true;
	}

	gl::GLuint Shader::getUniformID(std::string identifier) const
	{
		return gl::glGetUniformLocation(this->program_id, identifier.c_str());
	}
}
