#ifndef VAST_SHADER_HPP
#define VAST_SHADER_HPP

// Vast
#include <vast/resource.hpp>

// Library
#include <glbinding/gl/types.h>

// Standard
#include <string>

namespace Vast
{
	struct ShaderUniforms_Model
	{
		gl::GLuint time;
		gl::GLuint proj_mat;
		gl::GLuint view_mat;
		gl::GLuint mod_mat;
		gl::GLuint color;
		gl::GLuint texture;
	};

	struct ShaderUniforms_Skybox
	{
		gl::GLuint time;
		gl::GLuint proj_mat;
		gl::GLuint spin_mat;
		gl::GLuint cubemap;
	};

	class Shader : public Resource
	{
	public:
		enum class Type
		{
			MODEL,
			SKYBOX,
		};

	private:
		gl::GLuint vert_shader_id;
		gl::GLuint frag_shader_id;
		gl::GLuint program_id;

		Type type;

		union
		{
			ShaderUniforms_Model  uniforms_model;
			ShaderUniforms_Skybox uniforms_skybox;
		};

		void updateUniforms();

	public:
		Shader(Type type) { this->type = type; }

		gl::GLuint getProgramID() const { return this->program_id; }
		gl::GLuint getUniformID(std::string identifier) const;

		Type getType() const { return this->type; }
		const ShaderUniforms_Model& getModelUniforms() const { return this->uniforms_model; }
		const ShaderUniforms_Skybox& getSkyboxUniforms() const { return this->uniforms_skybox; }

		bool loadFiles(std::string vert_filename, std::string frag_filename);
		bool loadStrings(std::string vert_shader_code, std::string frag_shader_code);
	};
}

#endif
