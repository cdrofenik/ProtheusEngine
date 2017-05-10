#include "ObjectLoader.h"

using namespace math;

ObjectLoader::ObjectLoader()
{
}


ObjectLoader::~ObjectLoader()
{
}

ObjectLoader::LoadedObject ObjectLoader::loadObject(const std::string & filePath)
{
	std::vector<Vertex> inVertices;
	parseOBJ(filePath, inVertices);
	std::vector<Vertex> finalVertexData;
	std::vector<unsigned int> indices;
	createIndexedData(inVertices, finalVertexData, indices);

	LoadedObject result;
	GLuint vaoId;
	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);
	m_vaos.push_back(vaoId);
	result.vao = vaoId;

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, finalVertexData.size() * sizeof(Vertex), &finalVertexData[0], GL_STATIC_DRAW);
	m_vbos.push_back(vbo);
	result.vbo = vbo;

	GLuint eboId;
	glGenBuffers(1, &eboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
	m_ebos.push_back(eboId);
	result.ebo = eboId;

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textureCoordinates));

	glBindVertexArray(0);

	result.size = indices.size();
	return result;
}

void ObjectLoader::parseOBJ(const std::string & filePath, std::vector<Vertex>& vertexData)
{
	printf("[ProResourceLoader] Opening OBJ file: %s\n", filePath.c_str());

	std::vector<Vector3r> vertices;
	std::vector<Vector3r> normals;
	std::vector<Vector2r> textureCoords;
	std::vector<unsigned int> vertexIndices;
	std::vector<unsigned int> normalIndices;
	std::vector<unsigned int> textureCoordIndices;

	vertexData.clear();
	FILE * file;
	errno_t err;

	err = fopen_s(&file, filePath.c_str(), "r");
	if (file == NULL) {
		printf("[ProResourceLoader] Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		getchar();
	}

	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf_s(file, "%s", lineHeader, _countof(lineHeader));
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

				   // else : parse lineHeader
		if (strcmp(lineHeader, "v") == 0) {
			Real vertexx, vertexy, vertexz;
			fscanf_s(file, "%f %f %f\n", &vertexx, &vertexy, &vertexz);
			vertices.push_back(Vector3r(vertexx, vertexy, vertexz));
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			Real u, v;
			fscanf_s(file, "%f %f\n", &u, &v);
			textureCoords.push_back(Vector2r(u, v));
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			Real normalx, normaly, normalz;
			fscanf_s(file, "%f %f %f\n", &normalx, &normaly, &normalz);
			normals.push_back(Vector3r(normalx, normaly, normalz));
		}
		else if (strcmp(lineHeader, "f") == 0) {
			unsigned int vertexIndex[9];
			int matches = fscanf_s(file,
				"%d/%d/%d %d/%d/%d %d/%d/%d\n",
				&vertexIndex[0], &vertexIndex[1], &vertexIndex[2],
				&vertexIndex[3], &vertexIndex[4], &vertexIndex[5],
				&vertexIndex[6], &vertexIndex[7], &vertexIndex[8]);
			if (matches != 9) {
				printf("[ProResourceLoader] File can't be read by our simple parser :-( Try exporting with other options\n");
			}

			//vertex indices
			vertexIndices.push_back(vertexIndex[0] - 1);
			vertexIndices.push_back(vertexIndex[3] - 1);
			vertexIndices.push_back(vertexIndex[6] - 1);

			//texture indices
			textureCoordIndices.push_back(vertexIndex[1] - 1);
			textureCoordIndices.push_back(vertexIndex[4] - 1);
			textureCoordIndices.push_back(vertexIndex[7] - 1);

			//normal indices
			normalIndices.push_back(vertexIndex[2] - 1);
			normalIndices.push_back(vertexIndex[5] - 1);
			normalIndices.push_back(vertexIndex[8] - 1);
		}
		else {
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}
	}

	for (size_t i = 0; i < vertexIndices.size(); i++)
	{
		Vector3r vertex = vertices[vertexIndices[i]];
		Vector3r normal = normals[normalIndices[i]];
		Vector2r texture = textureCoords[textureCoordIndices[i]];
		Vertex currentVertex(vertex, normal, texture);

		vertexData.push_back(currentVertex);
	}
}

bool ObjectLoader::getSimilarVertexIndex(const Vertex& vertex,
	const std::vector<Vertex>& vertices, unsigned int& foundIndex)
{
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		if (vertex.isNear(vertices[i])) {
			foundIndex = i;
			return true;
		}
	}
	return false;
}

void ObjectLoader::createIndexedData(const std::vector<Vertex>& vertices, std::vector<Vertex>& finalVertices, std::vector<unsigned int>& indices)
{
	indices.clear();
	finalVertices.clear();

	for (size_t i = 0; i < vertices.size(); i++)
	{
		Vertex currentVertex = vertices[i];
		unsigned int foundIndex = 0;
		bool found = getSimilarVertexIndex(currentVertex, finalVertices, foundIndex);

		if (found) {
			indices.push_back(foundIndex);
		}
		else {
			finalVertices.push_back(currentVertex);
			indices.push_back(finalVertices.size() - 1);
		}
	}
}
