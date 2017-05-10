#pragma once

#include "core\math\Vector2.hpp"
#include "core\math\Vector3.hpp"

#include "GL\glew.h"

#include <string>
#include <vector>

class ObjectLoader
{
public:
	struct Vertex {
		math::Vector3r position = math::Vector3r(0.0f, 0.0f, 0.0f);
		math::Vector3r normal = math::Vector3r(0.0f, 0.0f, 0.0f);
		math::Vector2r textureCoordinates = math::Vector2r(0.0f, 0.0f);

		Vertex(math::Vector3r pos, math::Vector3r norm, math::Vector2r texCoord) :
			position(pos),
			normal(norm),
			textureCoordinates(texCoord)
		{}

		bool isNear(const Vertex& v) const {
			return position.isNear(v.position) &&
				normal.isNear(v.normal) &&
				textureCoordinates.isNear(v.textureCoordinates);
		}
	};

	struct LoadedObject
	{
		GLuint vao;
		GLuint vbo;
		GLuint ebo;
		int size;

		void Draw() {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			glBindVertexArray(this->vao);
			glEnableVertexAttribArray(0); // Position
			glEnableVertexAttribArray(1); // Normal
			glEnableVertexAttribArray(2); // Texture
			glDrawElements(GL_TRIANGLES, this->size, GL_UNSIGNED_INT, 0);
			glDisableVertexArrayAttrib(this->vao, 0);
			glDisableVertexArrayAttrib(this->vao, 1);
			glDisableVertexArrayAttrib(this->vao, 2);
			glBindVertexArray(0);
		}
	};

	ObjectLoader();
	~ObjectLoader();

	LoadedObject loadObject(const std::string& filePath);

private:
	std::vector<unsigned int> m_vaos;
	std::vector<unsigned int> m_vbos;
	std::vector<unsigned int> m_ebos;

	void parseOBJ(const std::string& filePath, std::vector<Vertex>& vertexData);
	void createIndexedData(const std::vector<Vertex>& vertices,
		std::vector<Vertex>& finalVertices,
		std::vector<unsigned int>& indices);
	bool getSimilarVertexIndex(const Vertex& vertex,
		const std::vector<Vertex>& vertices, unsigned int& foundIndex);
};

