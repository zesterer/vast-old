#ifndef VAST_RENDERER_HPP
#define VAST_RENDERER_HPP

// Vast
#include <vast/shader.hpp>
#include <vast/model.hpp>
#include <vast/texture.hpp>
#include <vast/cubemap.hpp>

// Library
#include <glm/glm.hpp>

namespace Vast
{
	class Renderer
	{
	public:
		bool init();
		void clear(glm::vec3 color = glm::vec3(1, 1, 1));
		void renderSkybox(const Shader& shader, const Model& model, const CubeMap& cubemap, glm::mat4 proj_mat, glm::mat4 view_mat, float time);
		void renderModel(const Shader& shader, const Model& model, const Texture& texture, glm::mat4 proj_mat, glm::mat4 view_mat, glm::mat4 mod_mat, glm::vec3 color, float time);
	};
}

#endif
