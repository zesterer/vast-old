// Vast
#include <vast/image.hpp>
#include <vast/log.hpp>

// Library
#include <SOIL/SOIL.h>

namespace Vast
{
	Image::~Image()
	{
		this->unload();
	}

	void Image::unload()
	{
		if (this->loaded)
		{
			if (this->data != nullptr)
			{
				free(this->data);
				this->data = nullptr;
			}

			this->loaded = false;
		}
	}

	bool Image::load(std::string filename)
	{
		this->unload();

		this->data = SOIL_load_image(filename.c_str(), &this->size.x, &this->size.y, 0, SOIL_LOAD_RGB);

		g_log.write("Opened image '" + filename + "' of size " + std::to_string(this->size.x) + " x " + std::to_string(this->size.x));

		this->loaded = true;

		return true;
	}
}
