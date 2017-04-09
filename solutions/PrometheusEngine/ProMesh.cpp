#include "ProMesh.h"

ProMesh::ProMesh()
{	
}

ProMesh::~ProMesh()
{
	glDeleteVertexArrays(1, &this->m_vao);
	glDeleteBuffers(1, &this->m_vbo);
}

void ProMesh::Init()
{
	glGenVertexArrays(1, &this->m_vao);
	glGenBuffers(1, &this->m_vbo);
	m_size = 0;
}

void ProMesh::AddVertices(ProVertex data[], const int& length)
{
	m_size = length;

	glBindVertexArray(this->m_vao);
	
	glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo);
	glBufferData(GL_ARRAY_BUFFER, this->m_size * sizeof(ProVertex), &data[0], GL_STATIC_DRAW);

	// Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ProVertex), (GLvoid*)0);

	glBindVertexArray(0);

}

void ProMesh::Draw()
{
	// Draw mesh
	glBindVertexArray(this->m_vao);
	glDrawArrays(GL_TRIANGLES, 0, this->m_size);
	glBindVertexArray(0);
}