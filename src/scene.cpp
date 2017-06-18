// Vast
#include <vast/scene.hpp>
#include <vast/log.hpp>

#include <vast/mesh.hpp>
#include <vast/image.hpp>
#include <vast/texture.hpp>
#include <vast/cubemap.hpp>
#include <vast/model.hpp>

#include <vast/entity.hpp>

// Library
#include <glm/glm.hpp>

namespace Vast
{
	Shader model_shader(Shader::Type::MODEL);
	Shader skybox_shader(Shader::Type::SKYBOX);

	Model   craft_model;
	Texture craft_texture;

	CubeMap skybox_cubemap;
	Model   skybox_model;

	bool Scene::init(Heap& heap)
	{
		this->heap = &heap;

		rid nentity = this->heap->create<Entity>();

		// Load shaders
		model_shader.loadFiles("data/shaders/vert.glsl", "data/shaders/frag.glsl");
		skybox_shader.loadFiles("data/shaders/sky-vert.glsl", "data/shaders/sky-frag.glsl");

		Mesh craft_mesh("data/obj/craft.obj");
		craft_model.load(craft_mesh);

		Mesh skybox_mesh("data/obj/skybox.obj");
		skybox_model.load(skybox_mesh);

		Image sky_x_pos("data/gfx/skybox/sky_x_pos.png");
		Image sky_x_neg("data/gfx/skybox/sky_x_neg.png");
		Image sky_y_pos("data/gfx/skybox/sky_y_pos.png");
		Image sky_y_neg("data/gfx/skybox/sky_y_neg.png");
		Image sky_z_pos("data/gfx/skybox/sky_z_pos.png");
		Image sky_z_neg("data/gfx/skybox/sky_z_neg.png");
		skybox_cubemap.load(
			sky_x_pos,
			sky_x_neg,
			sky_y_pos,
			sky_y_neg,
			sky_z_pos,
			sky_z_neg
		);

		Image craft_image("data/gfx/test.png");
		craft_texture.load(craft_image);

		g_log.write("Initiated scene");

		return true;
	}

	void Scene::tick()
	{
		this->camera.tick(*this);
	}

	void Scene::handleInput(const InputState& inputstate)
	{
		this->camera.rot.x = this->camera.rot.x - inputstate.getCursorOffset().x * 0.1f;
		this->camera.rot.y = glm::max(-90.0f, glm::min(90.0f, this->camera.rot.y + inputstate.getCursorOffset().y * 0.1f));

		float speed = 0.25f;
		if (inputstate.getKeyState(InputState::Key::MOVE_UP))
			this->camera.pos += glm::vec3(speed * glm::cos(glm::radians(this->camera.rot.x)), speed * glm::sin(glm::radians(this->camera.rot.x)), 0);
		if (inputstate.getKeyState(InputState::Key::MOVE_LEFT))
			this->camera.pos += glm::vec3(speed * glm::cos(glm::radians(this->camera.rot.x + 90.0f)), speed * glm::sin(glm::radians(this->camera.rot.x + 90.0f)), 0);
		if (inputstate.getKeyState(InputState::Key::MOVE_DOWN))
			this->camera.pos += glm::vec3(speed * glm::cos(glm::radians(this->camera.rot.x + 180.0f)), speed * glm::sin(glm::radians(this->camera.rot.x + 180.0f)), 0);
		if (inputstate.getKeyState(InputState::Key::MOVE_RIGHT))
			this->camera.pos += glm::vec3(speed * glm::cos(glm::radians(this->camera.rot.x - 90.0f)), speed * glm::sin(glm::radians(this->camera.rot.x - 90.0f)), 0);
		if (inputstate.getKeyState(InputState::Key::MOVE_CROUCH))
			this->camera.pos.z -= speed;
		if (inputstate.getKeyState(InputState::Key::MOVE_JUMP))
			this->camera.pos.z += speed;
	}

	void Scene::draw(Renderer& renderer)
	{
		renderer.renderSkybox(skybox_shader, skybox_model, skybox_cubemap, this->camera.getProjMatrix(), this->camera.getSpinMatrix());
		renderer.renderModel(model_shader, craft_model, craft_texture, this->camera.getProjMatrix(), this->camera.getViewMatrix(), glm::mat4(1.0f), glm::vec3(1, 1, 1));
	}
}
