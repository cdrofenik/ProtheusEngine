#include "gameApp.h"
#include "ProTime.h"

#include <math.h>

gameApp::gameApp()
{
}


gameApp::~gameApp()
{
}

void gameApp::start()
{
	mesh.Init();

	ProVertex vertices[4] = { ProVertex(ProVector3r(-1.0f, -1.0f, 0.0f)),
		ProVertex(ProVector3r(0.0f, 1.0f, 0.0f)),
		ProVertex(ProVector3r(1.0f, -1.0f, 0.0f)),
		ProVertex(ProVector3r(0.0f, -1.0f, 1.0f))};

	int indices[12] = { 0, 1, 3,
						3, 1, 2,
						2, 1, 0,
						0, 2, 3};

	mesh.AddVertices(vertices, indices, 12);

	shader.AddVertexShader("..\\..\\res\\shaders\\basicShader.vs");
	shader.AddFragmentShader("..\\..\\res\\shaders\\basicShader.fs");
	shader.Compile();
}

ProReal temp = 0.0f;

void gameApp::update()
{
	temp += ProTime::getDelta();
	ProReal value = std::sin(temp);
	transform.setRotation(0.0f, value * 5, 0.0f);
}

void gameApp::render()
{
	shader.Bind();
	shader.SetUniformMatrix4F("model", transform.getTransformMatrix());

	mesh.Draw();
}

void gameApp::stop()
{
}

void gameApp::input()
{
}

