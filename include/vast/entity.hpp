#ifndef VAST_ENTITY_HPP
#define VAST_ENTITY_HPP

// Vast
#include <vast/resource.hpp>
#include <vast/sceneobject.hpp>
#include <vast/state.hpp>
#include <vast/model.hpp>
#include <vast/shader.hpp>
#include <vast/texture.hpp>

// Standard
#include <memory>

namespace Vast
{
	class Entity : public Resource, public SceneObject
	{
	private:
		DynamicState dynamic_state;

		std::shared_ptr<Model>   model;
		std::shared_ptr<Shader>  shader;
		std::shared_ptr<Texture> texture;

	protected:
		void tick_handler(SceneObject& parent) override
		{
			(void)parent;

			this->dynamic_state.tick(this->state);
		}

		void update_handler(SceneObject& parent) override
		{
			this->state.updateRelativeTo(parent.state.mat);
		}

	public:
		const DynamicState& getDynamicState() const { return this->dynamic_state; }

		std::shared_ptr<Model> getModel() const     { return this->model; }
		std::shared_ptr<Shader> getShader() const   { return this->shader; }
		std::shared_ptr<Texture> getTexture() const { return this->texture; }

		void setModel(std::shared_ptr<Model> model)       { this->model = model; }
		void setShader(std::shared_ptr<Shader> shader)    { this->shader = shader; }
		void setTexture(std::shared_ptr<Texture> texture) { this->texture = texture; }
	};
}

#endif
