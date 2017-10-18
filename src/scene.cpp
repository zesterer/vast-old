// Vast
#include <vast/scene.hpp>
#include <vast/log.hpp>
#include <vast/heap.hpp>

#include <vast/mesh.hpp>
#include <vast/image.hpp>
#include <vast/texture.hpp>
#include <vast/cubemap.hpp>
#include <vast/model.hpp>

// Library
#include <glm/glm.hpp>

namespace Vast
{
	std::shared_ptr<Shader> model_shader;
	std::shared_ptr<Shader> skybox_shader;

	std::shared_ptr<Entity>  craft_entity;
	std::shared_ptr<Model>   craft_model;
	std::shared_ptr<Texture> craft_texture;

	std::shared_ptr<CubeMap> skybox_cubemap;
	std::shared_ptr<Model>   skybox_model;

	bool Scene::init()
	{
		// Load model shader
		model_shader = std::make_shared<Shader>(Shader::Type::MODEL);
		model_shader->loadFiles("data/shaders/vert.glsl", "data/shaders/frag.glsl");

		// Load Skybox shader
		skybox_shader = std::make_shared<Shader>(Shader::Type::SKYBOX);
		skybox_shader->loadFiles("data/shaders/sky-vert.glsl", "data/shaders/sky-frag.glsl");

		Mesh craft_mesh("data/obj/craft.obj");
		craft_model = std::make_shared<Model>(craft_mesh);

		Image craft_image("data/gfx/test.png");
		craft_texture = std::make_shared<Texture>(craft_image);

		Mesh skybox_mesh("data/obj/skybox.obj");
		skybox_model = std::make_shared<Model>(skybox_mesh);

		craft_entity = std::make_shared<Entity>();
		this->root.addChild(craft_entity);
		craft_entity->setModel(craft_model);
		craft_entity->setTexture(craft_texture);
		craft_entity->setShader(model_shader);
		this->entities.push_back(craft_entity);

		craft_entity->addChild(this->camera);

		Image sky_x_pos("data/gfx/skybox/sky_x_pos.png");
		Image sky_x_neg("data/gfx/skybox/sky_x_neg.png");
		Image sky_y_pos("data/gfx/skybox/sky_y_pos.png");
		Image sky_y_neg("data/gfx/skybox/sky_y_neg.png");
		Image sky_z_pos("data/gfx/skybox/sky_z_pos.png");
		Image sky_z_neg("data/gfx/skybox/sky_z_neg.png");
		skybox_cubemap = std::make_shared<CubeMap>(
			sky_x_pos,
			sky_x_neg,
			sky_y_pos,
			sky_y_neg,
			sky_z_pos,
			sky_z_neg
		);

		g_log.write("Initiated scene");

		return true;
	}

	void Scene::tick()
	{
		this->root.tickChildren();
		this->root.updateChildren();
	}

	void Scene::handleInput(const InputState& inputstate)
	{
		this->camera->state.ori.x = this->camera->state.ori.x - inputstate.getCursorOffset().x * 0.1f;
		this->camera->state.ori.y = glm::max(-90.0f, glm::min(90.0f, this->camera->state.ori.y + inputstate.getCursorOffset().y * 0.1f));

		float speed = 0.25f;
		if (inputstate.getKeyState(InputState::Key::MOVE_UP))
			this->camera->state.pos += glm::vec3(speed * glm::cos(glm::radians(this->camera->state.ori.x)), speed * glm::sin(glm::radians(this->camera->state.ori.x)), 0);
		if (inputstate.getKeyState(InputState::Key::MOVE_LEFT))
			this->camera->state.pos += glm::vec3(speed * glm::cos(glm::radians(this->camera->state.ori.x + 90.0f)), speed * glm::sin(glm::radians(this->camera->state.ori.x + 90.0f)), 0);
		if (inputstate.getKeyState(InputState::Key::MOVE_DOWN))
			this->camera->state.pos += glm::vec3(speed * glm::cos(glm::radians(this->camera->state.ori.x + 180.0f)), speed * glm::sin(glm::radians(this->camera->state.ori.x + 180.0f)), 0);
		if (inputstate.getKeyState(InputState::Key::MOVE_RIGHT))
			this->camera->state.pos += glm::vec3(speed * glm::cos(glm::radians(this->camera->state.ori.x - 90.0f)), speed * glm::sin(glm::radians(this->camera->state.ori.x - 90.0f)), 0);
		if (inputstate.getKeyState(InputState::Key::MOVE_CROUCH))
			this->camera->state.pos.z -= speed;
		if (inputstate.getKeyState(InputState::Key::MOVE_JUMP))
			this->camera->state.pos.z += speed;
	}

	void Scene::draw(Renderer& renderer)
	{
		renderer.renderSkybox(*skybox_shader, *skybox_model, *skybox_cubemap, this->camera->getProjMatrix(), this->camera->getSpinMatrix());

		for (std::shared_ptr<Entity> entity : this->entities)
			this->drawEntity(renderer, *entity);
	}

	void Scene::drawEntity(Renderer& renderer, const Entity& entity)
	{
		renderer.renderModel(*entity.getShader(), *entity.getModel(), *entity.getTexture(), this->camera->getProjMatrix(), this->camera->getViewMatrix(), entity.state.mat, glm::vec3(1, 1, 1));
	}
}
