// Vast
#include <vast/scene.hpp>
#include <vast/log.hpp>
#include <vast/heap.hpp>

#include <vast/voxelentity.hpp>
#include <vast/entity.hpp>
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

	std::shared_ptr<Entity>  craft_entity0;
	std::shared_ptr<Entity>  craft_entity;
	std::shared_ptr<Model>   craft_model;
	std::shared_ptr<Texture> craft_texture;

	std::shared_ptr<CubeMap> skybox_cubemap;
	std::shared_ptr<Model>   skybox_model;

	std::shared_ptr<VoxelEntity>  craft;

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

		craft_entity0 = std::make_shared<Entity>();
		this->root.addChild(craft_entity0);
		craft_entity0->setModel(craft_model);
		craft_entity0->setTexture(craft_texture);
		craft_entity0->setShader(model_shader);
		craft_entity0->state.pos = glm::vec3(10, 0, 0);

		craft_entity = std::make_shared<Entity>();
		this->root.addChild(craft_entity);
		craft_entity->setModel(craft_model);
		craft_entity->setTexture(craft_texture);
		craft_entity->setShader(model_shader);
		//craft_entity->state.rot = glm::quat(glm::vec3(0.0, 0.0, 0.01));

		this->camera->state.pos = glm::vec3(-20, 0, 5);
		craft_entity->addChild(this->camera);
		//this->root.addChild(this->camera);

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
		//this->root.tickChildren();
		//this->root.updateChildren();

		this->root.eventChildren(SceneEvent(SceneEvent::Type::TICK));
		this->root.eventChildren(SceneEvent(SceneEvent::Type::UPDATE));

		this->time += 1.0f / 60.0f;
	}

	void Scene::handleInput(const InputState& inputstate)
	{
		this->camera->state.ori *= glm::quat(glm::vec3(0, 0, 0.0015 * inputstate.getCursorOffset().x));
		this->camera->state.ori *= glm::quat(glm::vec3(0, -0.0015 * inputstate.getCursorOffset().y, 0));

		// Spin

		float spin_speed = 0.01;

		if (inputstate.getKeyState(InputState::Key::MOVE_SRIGHT))
			craft_entity->state.rot = glm::quat(craft_entity->state.ori * (glm::vec3(0, 0, -spin_speed))) * craft_entity->state.rot;
		if (inputstate.getKeyState(InputState::Key::MOVE_SLEFT))
			craft_entity->state.rot = glm::quat(craft_entity->state.ori * (glm::vec3(0, 0, spin_speed))) * craft_entity->state.rot;

		if (inputstate.getKeyState(InputState::Key::MOVE_SFORWARD))
			craft_entity->state.rot = glm::quat(craft_entity->state.ori * (glm::vec3(0, spin_speed, 0))) * craft_entity->state.rot;
		if (inputstate.getKeyState(InputState::Key::MOVE_SBACKWARD))
			craft_entity->state.rot = glm::quat(craft_entity->state.ori * (glm::vec3(0, -spin_speed, 0))) * craft_entity->state.rot;

		if (inputstate.getKeyState(InputState::Key::MOVE_SCCW))
			craft_entity->state.rot = glm::quat(craft_entity->state.ori * (glm::vec3(-spin_speed, 0, 0))) * craft_entity->state.rot;
		if (inputstate.getKeyState(InputState::Key::MOVE_SCW))
			craft_entity->state.rot = glm::quat(craft_entity->state.ori * (glm::vec3(spin_speed, 0, 0))) * craft_entity->state.rot;

		// Spin deceleration
		craft_entity->state.rot = glm::mix(craft_entity->state.rot, glm::quat(), 0.1f * craft_entity->state.rot.w);

		// Movement

		float speed = 0.1f;

		if (inputstate.getKeyState(InputState::Key::MOVE_UP))
			craft_entity->state.vel += craft_entity->state.ori * glm::vec3(speed, 0, 0);
		if (inputstate.getKeyState(InputState::Key::MOVE_DOWN))
			craft_entity->state.vel += craft_entity->state.ori * glm::vec3(-speed, 0, 0);

		if (inputstate.getKeyState(InputState::Key::MOVE_LEFT))
			craft_entity->state.vel += craft_entity->state.ori * glm::vec3(0, speed, 0);
		if (inputstate.getKeyState(InputState::Key::MOVE_RIGHT))
			craft_entity->state.vel += craft_entity->state.ori * glm::vec3(0, -speed, 0);

		if (inputstate.getKeyState(InputState::Key::MOVE_CROUCH))
			craft_entity->state.vel += craft_entity->state.ori * glm::vec3(0, 0, -speed);
		if (inputstate.getKeyState(InputState::Key::MOVE_JUMP))
			craft_entity->state.vel += craft_entity->state.ori * glm::vec3(0, 0, speed);

		// Movement deceleration
		if (glm::length(craft_entity->state.vel) > 0)
			craft_entity->state.vel -= 0.1f * glm::normalize(craft_entity->state.vel) * glm::pow(glm::length(craft_entity->state.vel), 1.0f);
	}

	void Scene::draw(Renderer& renderer)
	{
		renderer.renderSkybox(*skybox_shader, *skybox_model, *skybox_cubemap, this->camera->getProjMatrix(), this->camera->getSpinMatrix(), this->time);

		this->drawSceneObject(renderer, this->root);
	}

	void Scene::drawSceneObject(Renderer& renderer, const SceneObject& obj)
	{
		if (typeid(obj) == typeid(Entity))
			this->drawEntity(renderer, dynamic_cast<const Entity&>(obj));

		for (std::weak_ptr<SceneObject> child : obj.children)
		{
			if (std::shared_ptr<SceneObject> ptr = child.lock())
				this->drawSceneObject(renderer, *ptr);
		}
	}

	void Scene::drawEntity(Renderer& renderer, const Entity& entity)
	{
		glm::mat4 vm = this->camera->getViewMatrix();//glm::inverse(this->camera->getViewMatrix());

		renderer.renderModel(*entity.getShader(), *entity.getModel(), *entity.getTexture(), this->camera->getProjMatrix(), vm, entity.state.mat, glm::vec3(1, 1, 1), this->time);
	}
}
