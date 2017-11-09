#ifndef VAST_VOLUME_HPP
#define VAST_VOLUME_HPP

namespace Vast
{
	class Volume
	{
	private:
		std::vector<int> blocks;
		glm::ivec3 sz;

	public:
		Volume(glm::ivec3 size) : sz(size)
		{
			this->blocks.reserve(this->sz.x * this->sz.y * this->sz.z);
		}

		int get(glm::ivec3 p)
		{
			if (
				p.x > 0 && p.x < this->sz.x &&
				p.y > 0 && p.y < this->sz.y &&
				p.z > 0 && p.z < this->sz.z
			)
				return this->blocks[p.x * this->sz.y * this->sz.z + p.y * this->sz.z + p.z];
			else
				return 0;
		}

		void set(glm::ivec3 p, int b) { this->blocks[p.x * this->sz.y * this->sz.z + p.y * this->sz.z + p.z] = b; }
		glm::ivec3 size() { return this->sz; }
	};
}

#endif
