#pragma once

#include "core\math\Vector2.hpp"
#include "core\math\Vector3.hpp"

#include "GL\glew.h"

#include <string>
#include <vector>

class OBJLoader
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

	struct RenderData //Renderer data
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

	struct Mesh {
		std::vector<math::Vector3r> positions;
		std::vector<math::Vector3r> normals;
		std::vector<math::Vector2r> textureCoordinates;
		std::vector<unsigned int> indices;

		RenderData rd;
	};

	OBJLoader();
	~OBJLoader();

	Mesh loadObject(const std::string& filePath);

private:
	std::vector<GLuint> m_vaos;
	std::vector<GLuint> m_vbos;
	std::vector<GLuint> m_ebos;

	void parseOBJ(const std::string& filePath,
		std::vector<math::Vector3r>& out_positions,
		std::vector<math::Vector3r>& out_normals,
		std::vector<math::Vector2r>& out_textureIds);

	void createIndexedData(
		const std::vector<math::Vector3r> in_positions,
		const std::vector<math::Vector3r> in_normals,
		const std::vector<math::Vector2r> in_textureIds,
		std::vector<math::Vector3r>& out_positions,
		std::vector<math::Vector3r>& out_normals,
		std::vector<math::Vector2r>& out_textureIds,
		std::vector<unsigned int>& indices);

	bool getSimilarVertexIndex(const math::Vector3r& position,
		const math::Vector3r& normal,
		const math::Vector2r& texturedID,
		const std::vector<math::Vector3r>& positions,
		const std::vector<math::Vector3r>& normals,
		const std::vector<math::Vector2r>& textureIDs,
		unsigned int& foundIndex);
};

