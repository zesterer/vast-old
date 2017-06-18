#ifndef VAST_RENDERCONFIG_HPP
#define VAST_RENDERCONFIG_HPP

// Vast
#include <vast/shader.hpp>
#include <vast/model.hpp>
#include <vast/texture.hpp>
#include <vast/cubemap.hpp>

// Library
#include <glm/glm.hpp>

namespace Vast
{
	class RenderConfig
	{
		const Shader* shader;
		const Model*  model;

		RenderConfig(const Shader& shader);

		void setModel(const Model& model;);
	};

	struct RenderUniform
	{
		enum class Type
		{
			VEC2,
			VEC3,
			TEXTURE,
			CUBEMAP,
		};
	};
}

#endif
