// Vast
#include <vast/renderer.hpp>
#include <vast/log.hpp>

// Library
#include <glbinding/Binding.h>
#include <glbinding/gl/gl.h>

namespace Vast
{
	bool Renderer::init()
	{
		// Init glbinding
		glbinding::Binding::initialize();

		// Load shaders
		this->shader.loadFiles("data/shaders/vert.glsl", "data/shaders/frag.glsl");
		gl::glUseProgram(this->shader.getProgramID());

		// Enable GL features
		gl::glEnable(gl::GL_CULL_FACE);
		gl::glEnable(gl::GL_DEPTH_TEST);
		gl::glDepthFunc(gl::GL_LESS);

		g_log.write("Initiated renderer");

		return true;
	}

	void Renderer::clear(glm::vec3 color)
	{
		// Clear screen
		gl::glClearColor(color.r, color.g, color.b, 1.0);
		gl::glClear(gl::GL_COLOR_BUFFER_BIT | gl::GL_DEPTH_BUFFER_BIT);
	}
}
