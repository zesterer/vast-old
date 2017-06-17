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
	private:
		const Shader* shader = nullptr;

	public:
		bool init();
		void clear(glm::vec3 color = glm::vec3(1, 1, 1));
		void setShader(const Shader& shader);
		void renderCubeMap(const Model& model, const CubeMap& cubemap, glm::mat4 proj_mat, glm::mat4 view_mat, glm::vec3 cam_pos);
		void renderModel(const Model& model, const Texture& texture, glm::mat4 proj_mat, glm::mat4 view_mat, glm::mat4 mod_mat, glm::vec3 color = glm::vec3(1, 1, 1));
	};
}

#endif
