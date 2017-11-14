// Vast
#include <vast/mesh.hpp>

// Library
#include <glbinding/gl/gl.h>

// Standard
#include <fstream>
#include <sstream>
#include <cstdio>

namespace Vast
{
	std::vector<gl::GLfloat> Mesh::getVertexArray(Vertex::Format format) const
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

			if (format == Vertex::Format::POS_COL_NORM_UV)
			{
				array.push_back(p.v0.uv.x);
				array.push_back(p.v0.uv.y);
			}

			array.push_back(p.v1.pos.x);
			array.push_back(p.v1.pos.y);
			array.push_back(p.v1.pos.z);
			array.push_back(p.v1.col.r);
			array.push_back(p.v1.col.g);
			array.push_back(p.v1.col.b);
			array.push_back(p.v1.norm.x);
			array.push_back(p.v1.norm.y);
			array.push_back(p.v1.norm.z);

			if (format == Vertex::Format::POS_COL_NORM_UV)
			{
				array.push_back(p.v1.uv.x);
				array.push_back(p.v1.uv.y);
			}

			array.push_back(p.v2.pos.x);
			array.push_back(p.v2.pos.y);
			array.push_back(p.v2.pos.z);
			array.push_back(p.v2.col.r);
			array.push_back(p.v2.col.g);
			array.push_back(p.v2.col.b);
			array.push_back(p.v2.norm.x);
			array.push_back(p.v2.norm.y);
			array.push_back(p.v2.norm.z);

			if (format == Vertex::Format::POS_COL_NORM_UV)
			{
				array.push_back(p.v2.uv.x);
				array.push_back(p.v2.uv.y);
			}
		}

		return array;
	}

	bool Mesh::load(std::string filename)
	{
		std::ifstream filestream(filename);
		std::stringstream line;

		OBJModel objmodel;

		this->clear();

		if (filestream.is_open())
		{
			while (filestream.good())
			{
				char c = filestream.get();

				switch (c)
				{
				case '\n':
					{
						objmodel.parseLine(line.str());
						line.str(std::string());
					}
					break;

				default:
					line << c;
					break;
				}
			}

			for (long i = 0; i < objmodel.getPolygonCount(); i ++)
				this->add(objmodel.getPolygon(i));

			return true;
		}
		else
			std::printf("Could not open file!\n");

		return false;
	}

	void OBJModel::parseLine(std::string line)
	{
		float f0;
		float f1;
		float f2;
		long l0;
		long l1;
		long l2;
		long l3;
		long l4;
		long l5;
		long l6;
		long l7;
		long l8;

		// Ignore comments
		if (line[0] == '#')
			return;
		// Try vertex coords format
		else if (std::sscanf(line.c_str(), "v %f %f %f", &f0, &f1, &f2) >= 3)
			this->vertices.push_back(glm::vec3(f0, f1, f2));
		// Try vertex textcoords format
		// else if (std::sscanf(line.c_str(), "vt %f %f %f", &f0, &f1, &f2) >= 3)
		// 	this->uvs.push_back(glm::vec3(f0, f1, f2));
		// Try vertex textcoords format
		else if (std::sscanf(line.c_str(), "vt %f %f", &f0, &f1) >= 2)
			this->uvs.push_back(glm::vec2(f0, f1));
		// Try vertex normal format
		else if (std::sscanf(line.c_str(), "vn %f %f %f", &f0, &f1, &f2) >= 3)
			this->normals.push_back(glm::vec3(f0, f1, f2));
		// Try face format 1
		else if (std::sscanf(line.c_str(), "f %li %li %li", &l0, &l1, &l2) >= 3)
			this->polygons.push_back(std::tuple<
			glm::ivec3, glm::ivec3, glm::ivec3
		>(glm::ivec3(l0 - 1, l1 - 1, l2 - 1), glm::ivec3(-1, -1, -1), glm::ivec3(-1, -1, -1)));
		// Try face format 2
		else if (std::sscanf(line.c_str(), "f %li/%li/%li %li/%li/%li %li/%li/%li", &l0, &l1, &l2, &l3, &l4, &l5, &l6, &l7, &l8) >= 3)
			this->polygons.push_back(std::tuple<
			glm::ivec3, glm::ivec3, glm::ivec3
		>(glm::ivec3(l0 - 1, l3 - 1, l6 - 1), glm::ivec3(l1 - 1, l4 - 1, l7 - 1), glm::ivec3(l2 - 1, l5 - 1, l8 - 1)));
		// Try face format 3
		else if (std::sscanf(line.c_str(), "f %li//%li %li//%li %li//%li", &l0, &l1, &l2, &l3, &l4, &l5) >= 6)
			this->polygons.push_back(std::tuple<
			glm::ivec3, glm::ivec3, glm::ivec3
		>(glm::ivec3(l0 - 1, l2 - 1, l4 - 1), glm::ivec3(-1, -1, -1), glm::ivec3(l1 - 1, l3 - 1, l5 - 1)));
		// Try face format 4
		else if (std::sscanf(line.c_str(), "f %li/%li %li/%li %li/%li", &l0, &l1, &l2, &l3, &l4, &l5) >= 6)
			this->polygons.push_back(std::tuple<
			glm::ivec3, glm::ivec3, glm::ivec3
		>(glm::ivec3(l0 - 1, l2 - 1, l4 - 1), glm::ivec3(l1 - 1, l3 - 1, l5 - 1), glm::ivec3(-1, -1, -1)));
	}

	Polygon OBJModel::getPolygon(long i) const
	{
		Polygon p;
		std::tuple<glm::ivec3, glm::ivec3, glm::ivec3> indices = this->polygons[i];

		p.v1.col = glm::vec3(1, 1, 1);
		p.v0.col = glm::vec3(1, 1, 1);
		p.v2.col = glm::vec3(1, 1, 1);

		if (std::get<0>(indices).x >= 0) p.v0.pos = this->vertices[std::get<0>(indices).x];
		if (std::get<0>(indices).y >= 0) p.v1.pos = this->vertices[std::get<0>(indices).y];
		if (std::get<0>(indices).z >= 0) p.v2.pos = this->vertices[std::get<0>(indices).z];

		if (std::get<1>(indices).x >= 0) p.v0.uv = this->uvs[std::get<1>(indices).x];
		if (std::get<1>(indices).y >= 0) p.v1.uv = this->uvs[std::get<1>(indices).y];
		if (std::get<1>(indices).z >= 0) p.v2.uv = this->uvs[std::get<1>(indices).z];

		if (std::get<2>(indices).x >= 0) p.v0.norm = this->normals[std::get<2>(indices).x];
		if (std::get<2>(indices).y >= 0) p.v1.norm = this->normals[std::get<2>(indices).y];
		if (std::get<2>(indices).z >= 0) p.v2.norm = this->normals[std::get<2>(indices).z];

		p.normalize();

		return p;
	}
}
