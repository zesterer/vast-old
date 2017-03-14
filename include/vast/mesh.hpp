#ifndef VAST_MESH_HPP
#define VAST_MESH_HPP

// Library
#include <glm/glm.hpp>
#include <glbinding/gl/types.h>

// Standard
#include <vector>

namespace Vast
{
	struct Vertex
	{
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

	struct Mesh
	{
		std::vector<Polygon> polygons;

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

		const gl::GLfloat* getVertexArray()
		{
			return (const gl::GLfloat*)&this->polygons[0];
		}

		/*
		std::vector<gl::GLfloat> getVertexArray()
		{
			std::vector<gl::GLfloat> array;

			for (Polygon p : this->polygons)
			{
				array.push_back(p.v0.pos.x);
				array.push_back(p.v0.pos.y);
				array.push_back(p.v0.pos.z);
				array.push_back(p.v0.col.r);
				array.push_back(p.v0.col.g);
				array.push_back(p.v0.col.b);
				array.push_back(p.v0.norm.x);
				array.push_back(p.v0.norm.y);
				array.push_back(p.v0.norm.z);

				array.push_back(p.v1.pos.x);
				array.push_back(p.v1.pos.y);
				array.push_back(p.v1.pos.z);
				array.push_back(p.v1.col.r);
				array.push_back(p.v1.col.g);
				array.push_back(p.v1.col.b);
				array.push_back(p.v1.norm.x);
				array.push_back(p.v1.norm.y);
				array.push_back(p.v1.norm.z);

				array.push_back(p.v2.pos.x);
				array.push_back(p.v2.pos.y);
				array.push_back(p.v2.pos.z);
				array.push_back(p.v2.col.r);
				array.push_back(p.v2.col.g);
				array.push_back(p.v2.col.b);
				array.push_back(p.v2.norm.x);
				array.push_back(p.v2.norm.y);
				array.push_back(p.v2.norm.z);
			}

			return array;
		}
		*/
	};
}

#endif
