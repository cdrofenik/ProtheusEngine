#pragma once

#include "ProVertex.h"

#include "GL\glew.h"


class ProMesh
{
public:
	ProMesh();
	~ProMesh();


	void Init();
	void AddVertices(ProVertex vertices[], int indices[], const int& length);
	void Draw();

private:
	GLuint m_vao, m_vbo, m_ibo;
	int m_size;
};
