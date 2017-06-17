// Vast
#include <vast/renderer.hpp>
#include <vast/log.hpp>

// Library
#include <glbinding/Binding.h>
#include <glbinding/gl/gl.h>

// Standard
#include <iostream>

namespace Vast
{
	bool Renderer::init()
	{
		// Init glbinding
		glbinding::Binding::initialize();

		// Enable GL features
		gl::glEnable(gl::GL_CULL_FACE);
		gl::glEnable(gl::GL_DEPTH_TEST);
		gl::glDepthFunc(gl::GL_LESS);

		g_log.write("Initiated renderer");

		return true;
	}

	void Renderer::clear(glm::vec3 color)
	{
		// Clear screen
		gl::glClearColor(color.r, color.g, color.b, 1.0);
		gl::glClear(gl::GL_COLOR_BUFFER_BIT | gl::GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::setShader(const Shader& shader)
	{
		this->shader = &shader;
		gl::glUseProgram(this->shader->getProgramID());
	}

	void Renderer::renderModel(const Model& model, const Texture& texture, glm::mat4 proj_mat, glm::mat4 view_mat, glm::mat4 mod_mat, glm::vec3 color)
	{
		if (this->shader == nullptr)
			return;

		// Uniform IDs
		gl::GLuint uniform_proj_mat_id = this->shader->getUniformID("uni_proj_mat");
		gl::GLuint uniform_view_mat_id = this->shader->getUniformID("uni_view_mat");
		gl::GLuint uniform_mod_mat_id = this->shader->getUniformID("uni_mod_mat");
		gl::GLuint uniform_color_id = this->shader->getUniformID("uni_color");
		gl::GLuint uniform_texture_id = this->shader->getUniformID("uni_texture");

		// Bind the array & buffer and draw it
		gl::glBindVertexArray(model.getVertexArrayID());

		// Texture
		gl::glUniform1i(uniform_texture_id, 0);
		gl::glActiveTexture(gl::GL_TEXTURE0);
		gl::glBindTexture(gl::GL_TEXTURE_2D, texture.getTextureID());

		// Set uniform values
		gl::glUniformMatrix4fv(uniform_proj_mat_id, 1, gl::GL_FALSE, &proj_mat[0][0]);
		gl::glUniformMatrix4fv(uniform_view_mat_id, 1, gl::GL_FALSE, &view_mat[0][0]);
		gl::glUniformMatrix4fv(uniform_mod_mat_id, 1, gl::GL_FALSE, &mod_mat[0][0]);
		gl::glUniform3f(uniform_color_id, color.r, color.g, color.b);

		//gl::glBindBuffer(gl::GL_ARRAY_BUFFER, model.getVertexBufferID());
		gl::glDrawArrays(gl::GL_TRIANGLES, 0, model.getVertexCount());
	}

	void Renderer::renderCubeMap(const Model& model, const CubeMap& cubemap, glm::mat4 proj_mat, glm::mat4 view_mat, glm::vec3 cam_pos)
	{
		if (this->shader == nullptr)
			return;

		gl::glDepthMask(gl::GL_FALSE);

		// Uniform IDs
		gl::GLuint uniform_proj_mat_id = this->shader->getUniformID("uni_proj_mat");
		gl::GLuint uniform_view_mat_id = this->shader->getUniformID("uni_view_mat");
		gl::GLuint uniform_cubemap_id = this->shader->getUniformID("uni_cubemap");
		gl::GLuint uniform_cam_pos_id = this->shader->getUniformID("uni_cam_pos");

		// Bind the array & buffer and draw it
		gl::glBindVertexArray(model.getVertexArrayID());

		// Texture
		gl::glUniform1i(uniform_cubemap_id, 0);
		gl::glActiveTexture(gl::GL_TEXTURE0);
		gl::glBindTexture(gl::GL_TEXTURE_CUBE_MAP, cubemap.getCubeMapID());

		// Set uniform values
		gl::glUniformMatrix4fv(uniform_proj_mat_id, 1, gl::GL_FALSE, &proj_mat[0][0]);
		gl::glUniformMatrix4fv(uniform_view_mat_id, 1, gl::GL_FALSE, &view_mat[0][0]);
		gl::glUniform3f(uniform_cam_pos_id, cam_pos.x, cam_pos.y, cam_pos.z);

		//gl::glBindBuffer(gl::GL_ARRAY_BUFFER, model.getVertexBufferID());
		gl::glDrawArrays(gl::GL_TRIANGLES, 0, model.getVertexCount());

		gl::glDepthMask(gl::GL_TRUE);
	}
}