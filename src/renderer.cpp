// Vast
#include <vast/renderer.hpp>
#include <vast/log.hpp>

// Library
#include <glbinding/Binding.h>
#include <glbinding/gl/gl.h>

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

	void Renderer::renderModel(const Shader& shader, const Model& model, const Texture& texture, glm::mat4 proj_mat, glm::mat4 view_mat, glm::mat4 mod_mat, glm::vec3 color, float time)
	{
		if (shader.getType() != Shader::Type::MODEL)
		{
			g_log.write("Attempted to render model with inappropriate shader");
			return;
		}

		// Use the shader
		gl::glUseProgram(shader.getProgramID());

		// Set uniform values
		gl::glUniform1f(shader.getModelUniforms().time, time);
		gl::glUniformMatrix4fv(shader.getModelUniforms().proj_mat, 1, gl::GL_FALSE, &proj_mat[0][0]);
		gl::glUniformMatrix4fv(shader.getModelUniforms().view_mat, 1, gl::GL_FALSE, &view_mat[0][0]);
		gl::glUniformMatrix4fv(shader.getModelUniforms().mod_mat, 1, gl::GL_FALSE, &mod_mat[0][0]);
		gl::glUniform3f(shader.getModelUniforms().color, color.r, color.g, color.b);

		// Texture
		gl::glUniform1i(shader.getModelUniforms().texture, 0);
		gl::glActiveTexture(gl::GL_TEXTURE0);
		gl::glBindTexture(gl::GL_TEXTURE_2D, texture.getTextureID());

		// Bind the array & buffer and draw it
		gl::glBindVertexArray(model.getVertexArrayID());
		gl::glBindBuffer(gl::GL_ARRAY_BUFFER, model.getVertexBufferID());

		gl::glDrawArrays(gl::GL_TRIANGLES, 0, model.getVertexCount());
	}

	void Renderer::renderSkybox(const Shader& shader, const Model& model, const CubeMap& cubemap, glm::mat4 proj_mat, glm::mat4 spin_mat, float time)
	{
		if (shader.getType() != Shader::Type::SKYBOX)
		{
			g_log.write("Attempted to render skybox with inappropriate shader");
			return;
		}

		// Use the shader
		gl::glUseProgram(shader.getProgramID());

		// Set uniform values
		gl::glUniform1f(shader.getSkyboxUniforms().time, time);
		gl::glUniformMatrix4fv(shader.getSkyboxUniforms().proj_mat, 1, gl::GL_FALSE, &proj_mat[0][0]);
		gl::glUniformMatrix4fv(shader.getSkyboxUniforms().spin_mat, 1, gl::GL_FALSE, &spin_mat[0][0]);

		// Texture
		gl::glUniform1i(shader.getSkyboxUniforms().cubemap, 0);
		gl::glActiveTexture(gl::GL_TEXTURE0);
		gl::glBindTexture(gl::GL_TEXTURE_CUBE_MAP, cubemap.getCubeMapID());

		// Bind the array & buffer and draw it
		gl::glBindVertexArray(model.getVertexArrayID());
		gl::glBindBuffer(gl::GL_ARRAY_BUFFER, model.getVertexBufferID());

		gl::glDepthMask(gl::GL_FALSE); // Disable depth writing

		gl::glDrawArrays(gl::GL_TRIANGLES, 0, model.getVertexCount());

		gl::glDepthMask(gl::GL_TRUE); // Enable depth writing
	}
}
