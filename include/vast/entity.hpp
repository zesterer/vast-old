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
		std::shared_ptr<Model>   model;
		std::shared_ptr<Shader>  shader;
		std::shared_ptr<Texture> texture;

	protected:
		void event_handler(SceneObject& parent, SceneEvent event) override
		{
			switch (event.type)
			{
			case SceneEvent::Type::TICK:
				this->state.tick();
				break;

			case SceneEvent::Type::UPDATE:
				this->state.updateRelativeTo(parent.state.mat);
				break;

			default:
				break;
			}

			if (!event.cancelled)
				SceneObject::event_handler(parent, event);
		}

	public:
		std::shared_ptr<Model> getModel() const     { return this->model; }
		std::shared_ptr<Shader> getShader() const   { return this->shader; }
		std::shared_ptr<Texture> getTexture() const { return this->texture; }

		void setModel(std::shared_ptr<Model> model)       { this->model = model; }
		void setShader(std::shared_ptr<Shader> shader)    { this->shader = shader; }
		void setTexture(std::shared_ptr<Texture> texture) { this->texture = texture; }
	};
}

#endif
