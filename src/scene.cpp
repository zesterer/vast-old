// Vast
#include <vast/scene.hpp>
#include <vast/log.hpp>

// Library
#include <glm/glm.hpp>

namespace Vast
{
	Model model;
	Model skybox;
	Texture texture;

	bool Scene::init()
	{
		g_log.write("Initiated scene");

		Mesh mesh;
		mesh.add(Quad(glm::vec3(-1, -1, 0), glm::vec3(+1, -1, 0), glm::vec3(+1, +1, 0), glm::vec3(-1, +1, 0), glm::vec3(1, 1, 1), glm::vec3(0, 0, 1),
		glm::vec2(0, 1), glm::vec2(1, 1), glm::vec2(1, 0), glm::vec2(0, 0)));
		mesh.load("data/obj/craft.obj");
		model.load(mesh);

		Mesh skymesh;
		skymesh.load("data/obj/skybox.obj");
		skybox.load(skymesh);

		Image image("data/gfx/test.png");
		texture.load(image);

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
		//renderer.renderModel(model, texture, this->camera.getProjMatrix(), this->camera.getViewMatrix(), glm::mat4(1.0f), glm::vec3(1, 1, 1));
		renderer.renderModel(skybox, texture, this->camera.getProjMatrix(), this->camera.getViewMatrix(), glm::mat4(1.0f), glm::vec3(1, 1, 1));
	}
}
