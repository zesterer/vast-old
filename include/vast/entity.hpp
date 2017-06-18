#ifndef VAST_ENTITY_HPP
#define VAST_ENTITY_HPP

// Vast
#include <vast/resource.hpp>
#include <vast/state.hpp>
#include <vast/model.hpp>
#include <vast/shader.hpp>
#include <vast/texture.hpp>

// Standard
#include <memory>

namespace Vast
{
	class Entity : public Resource
	{
	private:
		DynamicState state;

		std::shared_ptr<Model>   model;
		std::shared_ptr<Shader>  shader;
		std::shared_ptr<Texture> texture;

	public:
		const DynamicState& getState() const { return this->state; }

		std::shared_ptr<Model> getModel() const     { return this->model; }
		std::shared_ptr<Shader> getShader() const   { return this->shader; }
		std::shared_ptr<Texture> getTexture() const { return this->texture; }

		void setModel(std::shared_ptr<Model> model)       { this->model = model; }
		void setShader(std::shared_ptr<Shader> shader)    { this->shader = shader; }
		void setTexture(std::shared_ptr<Texture> texture) { this->texture = texture; }

		void tick()
		{
			this->state.tick();
		}
	};
}

#endif
