#pragma once

#include "ProVertex.h"

#include "GL\glew.h"

#include <vector>


class ProMesh
{
public:
	ProMesh();
	~ProMesh();


	void Init();
	void AddVertices(ProVertex vertices[], int indices[], const int& length);
	void AddVertices(std::vector<ProVertex> vertices, std::vector<int> indices);
	void Draw();

private:
	GLuint m_vao, m_vbo, m_ibo;
	unsigned int m_size;
};
