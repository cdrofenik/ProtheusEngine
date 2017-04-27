#include "ProResourceLoader.h"

#include <vector>
#include <iostream>
#include <fstream>

#include <stdio.h>
#include <string>
#include <cstring>

std::string ProResourceLoader::GetStringFromFile(std::string filePath)
{
	std::string fileString;
	std::ifstream fileStream(filePath, std::ios::in);

	if (fileStream.is_open()) {
		std::string Line = "";
		while (getline(fileStream, Line))
			fileString += "\n" + Line;
		fileStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory?\n", filePath.c_str());
		getchar();
		return 0;
	}

	return fileString;
}

std::string ProResourceLoader::GetStringFromFile(const char* filePath)
{
	std::string fileString;
	std::ifstream fileStream(filePath, std::ios::in);

	if (fileStream.is_open()) {
		std::string Line = "";
		while (getline(fileStream, Line))
			fileString += "\n" + Line;
		fileStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory?\n", filePath);
		getchar();
		return 0;
	}

	return fileString;
}

bool ProResourceLoader::GetMeshFromFile(std::string filePath, ProMesh& outMesh)
{
	printf("Opening OBJ file: %s\n", filePath.c_str());

	std::vector<ProVertex> vertices;
	std::vector<int> indices;

	FILE * file;
	errno_t err;

	err = fopen_s(&file, filePath.c_str(), "r");
	if (file == NULL) {
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		getchar();
		return false;
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
			vertices.push_back(ProVertex(Vector3r(vertexx, vertexy, vertexz)));
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			//TODO
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			Real normalx, normaly, normalz;
			fscanf_s(file, "%f %f %f\n", &normalx, &normaly, &normalz);
			//normals.push_back(ProVertex(Vector3r(normalx, normaly, normalz)));
		}
		else if (strcmp(lineHeader, "f") == 0) {
			unsigned int vertexIndex[8];
			int matches = fscanf_s(file, "%d//%d %d//%d %d//%d %d//%d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2], &vertexIndex[3], &vertexIndex[4], &vertexIndex[5], &vertexIndex[6], &vertexIndex[7]);
			if (matches != 8) {
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				return false;
			}

			//vertex indices
			indices.push_back(vertexIndex[0] - 1);
			indices.push_back(vertexIndex[2] - 1);
			indices.push_back(vertexIndex[4] - 1);

			indices.push_back(vertexIndex[4] - 1);
			indices.push_back(vertexIndex[2] - 1);
			indices.push_back(vertexIndex[6] - 1);

			indices.push_back(vertexIndex[6] - 1);
			indices.push_back(vertexIndex[4] - 1);
			indices.push_back(vertexIndex[0] - 1);

			//normal indices
		}
		else {
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}
	}

	outMesh.AddVertices(vertices, indices);

	return true;
}
