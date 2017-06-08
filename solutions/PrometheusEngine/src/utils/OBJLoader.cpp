#include "OBJLoader.h"

using namespace math;

OBJLoader::OBJLoader()
{
}

OBJLoader::~OBJLoader()
{
}

OBJLoader::Mesh OBJLoader::loadObject(const std::string & filePath)
{
	std::vector<Vector3r> positions;
	std::vector<Vector3r> normals;
	std::vector<Vector2r> textureIDs;

	parseOBJ(filePath, positions, normals, textureIDs);
	std::vector<Vector3r> finalPositions;
	std::vector<Vector3r> finalNormals;
	std::vector<Vector2r> finalTextureIDs;
	std::vector<unsigned int> indices;
	createIndexedData(positions, normals, textureIDs, 
		finalPositions, finalNormals, finalTextureIDs, indices);

	Mesh resultingMesh;
	resultingMesh.positions = finalPositions;
	resultingMesh.normals = finalNormals;
	resultingMesh.textureCoordinates = finalTextureIDs;
	resultingMesh.indices = indices;

	//GLuint vaoId;
	//glGenVertexArrays(1, &vaoId);
	//glBindVertexArray(vaoId);
	//m_vaos.push_back(vaoId);
	//resultingMesh.rd.vao = vaoId;

	//GLuint vbo;
	//glGenBuffers(1, &vbo);
	//glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glBufferData(GL_ARRAY_BUFFER, finalVertexData.size() * sizeof(Vertex), &finalVertexData[0], GL_STATIC_DRAW);
	//m_vbos.push_back(vbo);
	//resultingMesh.rd.vbo = vbo;

	//GLuint eboId;
	//glGenBuffers(1, &eboId);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
	//m_ebos.push_back(eboId);
	//resultingMesh.rd.ebo = eboId;

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textureCoordinates));

	//glBindVertexArray(0);

	//resultingMesh.rd.size = indices.size();
	return resultingMesh;
}

void OBJLoader::parseOBJ(const std::string & filePath,
	std::vector<Vector3r>& out_positions,
	std::vector<Vector3r>& out_normals,
	std::vector<Vector2r>& out_textureIds)
{
	printf("[ProResourceLoader] Opening OBJ file: %s\n", filePath.c_str());

	std::vector<Vector3r> vertices;
	std::vector<Vector3r> normals;
	std::vector<Vector2r> textureCoords;
	std::vector<unsigned int> vertexIndices;
	std::vector<unsigned int> normalIndices;
	std::vector<unsigned int> textureCoordIndices;

	FILE * file;
	errno_t err;

	err = fopen_s(&file, filePath.c_str(), "r");
	if (file == NULL) {
		printf("[ProResourceLoader] Impossible to open the file ! Are you in the right path?\n");
		getchar();
	}

	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader, _countof(lineHeader));
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

				   // else : parse lineHeader
		if (strcmp(lineHeader, "v") == 0) {
			Real vertexx, vertexy, vertexz;
			fscanf(file, "%f %f %f\n", &vertexx, &vertexy, &vertexz);
			vertices.push_back(Vector3r(vertexx, vertexy, vertexz));
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			Real u, v;
			fscanf(file, "%f %f\n", &u, &v);
			textureCoords.push_back(Vector2r(u, v));
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			Real normalx, normaly, normalz;
			fscanf(file, "%f %f %f\n", &normalx, &normaly, &normalz);
			normals.push_back(Vector3r(normalx, normaly, normalz));
		}
		else if (strcmp(lineHeader, "f") == 0) {
			unsigned int vertexIndex[9];
			int matches = fscanf(file,
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

	out_positions.clear();
	out_positions.reserve(vertexIndices.size());
	out_normals.clear();
	out_normals.reserve(vertexIndices.size());
	out_textureIds.clear();
	out_textureIds.reserve(vertexIndices.size());
	for (unsigned int i = 0; i  < vertexIndices.size(); i ++)
	{
		out_positions.push_back(vertices[vertexIndices[i]]);
		out_normals.push_back(normals[normalIndices[i]]);
		out_textureIds.push_back(textureCoords[textureCoordIndices[i]]);
	}
}

bool OBJLoader::getSimilarVertexIndex(const Vector3r& position,
	const Vector3r& normal,
	const Vector2r& texturedID,
	const std::vector<Vector3r>& positions,
	const std::vector<Vector3r>& normals,
	const std::vector<Vector2r>& textureIDs,
	unsigned int& foundIndex)
{
	for (unsigned int i = 0; i < positions.size(); i++)
	{
		if (position.isNear(positions[i]) &&
			normal.isNear(normals[i]) &&
			texturedID.isNear(textureIDs[i])) {
			foundIndex = i;
			return true;
		}
	}
	return false;
}

void OBJLoader::createIndexedData(const std::vector<Vector3r> in_positions,
	const std::vector<Vector3r> in_normals,
	const std::vector<Vector2r> in_textureIds,
	std::vector<Vector3r>& out_positions,
	std::vector<Vector3r>& out_normals,
	std::vector<Vector2r>& out_textureIds,
	std::vector<unsigned int>& indices)
{
	indices.clear();
	for (size_t i = 0; i < in_positions.size(); i++)
	{
		//Vertex currentVertex = vertices[i];
		Vector3r position = in_positions[i];
		Vector3r normal = in_normals[i];
		Vector2r textureID = in_textureIds[i];

		unsigned int foundIndex = 0;
		bool found = getSimilarVertexIndex(position, normal, textureID,
			out_positions, out_normals, out_textureIds, foundIndex);

		if (found) {
			indices.push_back(foundIndex);
		}
		else {
			out_positions.push_back(position);
			out_normals.push_back(normal);
			out_textureIds.push_back(textureID);
			indices.push_back(out_positions.size() - 1);
		}
	}
}
