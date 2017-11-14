#ifndef VAST_MESH_HPP
#define VAST_MESH_HPP

// Library
#include <glm/glm.hpp>
#include <glbinding/gl/types.h>

// Standard
#include <vector>
#include <string>
#include <tuple>

namespace Vast
{
	struct Vertex
	{
		enum class Format
		{
			POS_COL_NORM,
			POS_COL_NORM_UV,
		};

		glm::vec3 pos;
		glm::vec3 col;
		glm::vec3 norm;
		glm::vec2 uv;

		Vertex() {}
		Vertex(glm::vec3 pos, glm::vec3 col, glm::vec3 norm, glm::vec2 uv = glm::vec2(0, 0))
		{
			this->pos = pos;
			this->col = col;
			this->norm = norm;
			this->uv = uv;
		}
	};

	struct Polygon
	{
		Vertex v0;
		Vertex v1;
		Vertex v2;

		Polygon() {}
		Polygon(Vertex v0, Vertex v1, Vertex v2)
		{
			this->v0 = v0;
			this->v1 = v1;
			this->v2 = v2;
		}

		void normalize()
		{
			glm::vec3 n = glm::cross(this->v1.pos - this->v0.pos, this->v2.pos - this->v0.pos);
			glm::normalize(n);

			this->v0.norm = n;
			this->v1.norm = n;
			this->v2.norm = n;
		}

		void offset(glm::vec3 off)
		{
			this->v0.pos += off;
			this->v1.pos += off;
			this->v2.pos += off;
		}
	};

	struct Quad
	{
		Polygon p0;
		Polygon p1;

		Quad() {}
		Quad(Vertex v0, Vertex v1, Vertex v2, Vertex v3)
		{
			this->p0.v0 = v0;
			this->p0.v1 = v1;
			this->p0.v2 = v2;

			this->p1.v0 = v0;
			this->p1.v1 = v2;
			this->p1.v2 = v3;
		}

		Quad(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 col, glm::vec3 norm, glm::vec2 uv0 = glm::vec2(0, 0), glm::vec2 uv1 = glm::vec2(0, 0), glm::vec2 uv2 = glm::vec2(0, 0), glm::vec2 uv3 = glm::vec2(0, 0))
		{
			this->p0.v0 = Vertex(p0, col, norm, uv0);
			this->p0.v1 = Vertex(p1, col, norm, uv1);
			this->p0.v2 = Vertex(p2, col, norm, uv2);

			this->p1.v0 = Vertex(p0, col, norm, uv0);
			this->p1.v1 = Vertex(p2, col, norm, uv2);
			this->p1.v2 = Vertex(p3, col, norm, uv3);
		}
	};

	class Mesh
	{
		std::vector<Polygon> polygons;

	public:
		Mesh() {}
		Mesh (std::string filename)
		{
			this->load(filename);
		}

		void clear()
		{
			this->polygons.clear();
		}

		void add(Polygon polygon)
		{
			this->polygons.push_back(polygon);
		}

		void add(Quad quad)
		{
			this->polygons.push_back(quad.p0);
			this->polygons.push_back(quad.p1);
		}

		void offset(glm::vec3 off)
		{
			for (Polygon& p : this->polygons)
				p.offset(off);
		}

		long getVertexCount() const
		{
			return this->polygons.size() * 3;
		}

		std::vector<gl::GLfloat> getVertexArray(Vertex::Format format = Vertex::Format::POS_COL_NORM_UV) const;

		bool load(std::string filename);
	};

	class OBJModel
	{
	private:
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> uvs;
		std::vector<std::tuple<glm::ivec3, glm::ivec3, glm::ivec3>> polygons;

	public:
		Polygon getPolygon(long i) const;
		long getPolygonCount() const { return this->polygons.size(); }

		void parseLine(std::string line);
	};
}

#endif
