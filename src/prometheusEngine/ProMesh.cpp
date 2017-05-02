#include "ProMesh.h"

ProMesh::ProMesh()
{
}

ProMesh::~ProMesh()
{
	glDeleteBuffers(1, &this->m_vbo);
	glDeleteBuffers(1, &this->m_ibo);
	glDeleteVertexArrays(1, &this->m_vao);
}

void ProMesh::Init()
{
	glGenVertexArrays(1, &this->m_vao);
	glGenBuffers(1, &this->m_vbo);
	glGenBuffers(1, &this->m_ibo);
	m_size = 0;
}

void ProMesh::AddVertices(ProVertex vertices[], int indices[], const int& length)
{
	m_size = length;

	glBindVertexArray(this->m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo);
	glBufferData(GL_ARRAY_BUFFER, this->m_size * sizeof(ProVertex), &vertices[0], GL_STATIC_DRAW);

	// Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ProVertex), (GLvoid*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->m_size * sizeof(int), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void ProMesh::AddVertices(std::vector<ProVertex> vertices, std::vector<int> indices)
{
	m_size = indices.size();

	glBindVertexArray(this->m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(ProVertex), &vertices[0], GL_STATIC_DRAW);

	// Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ProVertex), (GLvoid*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);

}

void ProMesh::Draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Draw mesh
	glBindVertexArray(this->m_vao);
	glDrawElements(GL_TRIANGLES, m_size, GL_UNSIGNED_INT, 0);
//	glDrawArrays(GL_TRIANGLES, 0, this->m_size);
	glBindVertexArray(0);
}