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

	std::shared_ptr<VoxelEntity> craft_entity;
	std::shared_ptr<Texture>     craft_texture;

	std::shared_ptr<CubeMap> skybox_cubemap;
	std::shared_ptr<Model>   skybox_model;

	std::shared_ptr<Entity>  rock;
	std::shared_ptr<Model>   rock_model;
	std::shared_ptr<Texture> rock_texture;

	bool Scene::init()
	{
		// Load model shader
		model_shader = std::make_shared<Shader>(Shader::Type::MODEL);
		model_shader->loadFiles("data/shaders/vert.glsl", "data/shaders/frag.glsl");

		// Load Skybox shader
		skybox_shader = std::make_shared<Shader>(Shader::Type::SKYBOX);
		skybox_shader->loadFiles("data/shaders/sky-vert.glsl", "data/shaders/sky-frag.glsl");

		// Mesh craft_mesh("data/obj/craft.obj");
		// craft_model = std::make_shared<Model>(craft_mesh);

		Image craft_image("data/gfx/test.png");
		craft_texture = std::make_shared<Texture>(craft_image);

		Mesh skybox_mesh("data/obj/skybox.obj");
		skybox_model = std::make_shared<Model>(skybox_mesh);

		// Craft
		{
			craft_entity = std::make_shared<VoxelEntity>("data/vox/craft.vox");
			this->root.addChild(craft_entity);
			craft_entity->setTexture(craft_texture);
			craft_entity->setShader(model_shader);
		}

		// Rock
		{
			Mesh rock_mesh("data/obj/rock.obj");
			Image rock_image("data/gfx/rock.png");

			rock_model = std::make_shared<Model>(rock_mesh);
			rock_texture = std::make_shared<Texture>(rock_image);

			rock = std::make_shared<Entity>();
			rock->state.pos = glm::vec3(100, 0, 0);
			rock->state.rot = glm::quat(glm::vec3(0.01, 0, 0));
			rock->setModel(rock_model);
			rock->setTexture(rock_texture);
			rock->setShader(model_shader);

			//rock->remesh();

			this->root.addChild(rock);
		}

		this->camera->state.pos = glm::vec3(1, 0, 0);
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
		this->root.eventChildren(SceneEvent(SceneEvent::Type::TICK));
		this->root.eventChildren(SceneEvent(SceneEvent::Type::UPDATE));

		this->time += 1.0f / 60.0f;
	}

	float cam_yaw = 0, cam_pitch = 0;
	bool flight_mode = false;

	void Scene::handleInput(const InputState& inputstate)
	{
		this->camera->state.ori *= glm::quat(glm::vec3(0, 0, 0.0015 * inputstate.getCursorOffset().x));
		this->camera->state.ori *= glm::quat(glm::vec3(0, -0.0015 * inputstate.getCursorOffset().y, 0));

		cam_yaw += 0.002f * inputstate.getCursorOffset().x;
		cam_pitch -= 0.002f * inputstate.getCursorOffset().y;

		this->camera->state.ori = glm::quat();
		this->camera->state.ori = glm::rotate(this->camera->state.ori, cam_pitch, glm::vec3(0, 1, 0));
		this->camera->state.ori = glm::rotate(this->camera->state.ori, cam_yaw, glm::vec3(0, 0, 1));

		// Mode switching

		for (const InputState::KeyEvent& e : inputstate.getEvents())
		{
			if (e.key == InputState::Key::SWITCH_MODE && e.pressed)
				flight_mode = !flight_mode;
		}

		// Spin

		if (flight_mode)
		{
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
		}
		else
		{
			glm::vec3 mx = glm::vec3(sin(cam_yaw), cos(cam_yaw), 0);
			glm::vec3 my = glm::vec3(cos(cam_yaw), -sin(cam_yaw), 0);

			if (inputstate.getKeyState(InputState::Key::MOVE_SRIGHT))
				this->camera->state.pos -= mx * 0.1f;
			if (inputstate.getKeyState(InputState::Key::MOVE_SLEFT))
				this->camera->state.pos += mx * 0.1f;
			if (inputstate.getKeyState(InputState::Key::MOVE_SFORWARD))
				this->camera->state.pos += my * 0.1f;
			if (inputstate.getKeyState(InputState::Key::MOVE_SBACKWARD))
				this->camera->state.pos -= my * 0.1f;

			if (inputstate.getKeyState(InputState::Key::MOVE_CROUCH))
				this->camera->state.pos.z -= 0.1f;
			if (inputstate.getKeyState(InputState::Key::MOVE_JUMP))
				this->camera->state.pos.z += 0.1f;
		}

		// Movement

		if (flight_mode)
		{
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
		}

		// Spin deceleration
		craft_entity->state.rot = glm::mix(craft_entity->state.rot, glm::quat(), 0.1f * craft_entity->state.rot.w);

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
		if (dynamic_cast<const Entity*>(&obj) != nullptr)
			this->drawEntity(renderer, reinterpret_cast<const Entity&>(obj));

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
