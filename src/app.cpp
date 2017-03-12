// Vast
#include <vast/app.hpp>
#include <vast/log.hpp>

namespace Vast
{
	class TestItem : public Resource
	{
	public:
		int a = 123;

		TestItem(int a)
		{
			this->a = a;
		}
	};

	App::App(int argc, char* argv[])
	{
		for (int i = 0; i < argc; i ++)
			this->args.emplace_back(argv[i]);

		g_log.write("Parsed app arguments");
	}

	int App::run()
	{
		g_log.write("App run procedure started");

		// Initiate all systems
		bool initiated = true;
		initiated &= this->window.open("Vast");
		initiated &= this->renderer.init();

		// Check for initiation failure
		if (initiated)
			g_log.write("Finished core systems initiation");
		else
		{
			g_log.write("Error : Initiation failure occured", Log::Mode::ERROR);
			this->close();
		}

		// Run the game
		this->running = true;
		while (this->running)
		{
			// Rendering
			this->renderer.clear(glm::vec3(1, 1, 1));
			this->window.display();

			// Input
			this->window.handleInput();
			if (!this->window.isOpen())
			{
				g_log.write("Window received close event");
				this->close();
			}
		}

		// Close all systems
		this->window.close();

		return 0;
	}

	void App::close()
	{
		this->running = false;
		g_log.write("App close event occured");
	}
}
