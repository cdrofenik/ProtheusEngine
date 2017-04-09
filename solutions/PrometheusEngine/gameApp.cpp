#include "gameApp.h"

gameApp::gameApp()
{
}


gameApp::~gameApp()
{
}

void gameApp::start()
{
	mesh.Init();

	ProVertex data[3] = { ProVertex(ProVector3r(-1.0f, -1.0f, 0.0f)),
		ProVertex(ProVector3r(0.0f, 1.0f, 0.0f)),
		ProVertex(ProVector3r(1.0f, -1.0f, 0.0f)) };

	mesh.AddVertices(data, 3);

	shader.AddVertexShader("..\\..\\res\\shaders\\basicShader.vs");
	shader.AddFragmentShader("..\\..\\res\\shaders\\basicShader.fs");
	shader.Compile();
}

void gameApp::render()
{
	shader.Bind();
	mesh.Draw();
}

void gameApp::stop()
{
}

void gameApp::input()
{
}

void gameApp::update()
{
}
