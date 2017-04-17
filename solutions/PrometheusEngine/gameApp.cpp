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

	ProVertex vertices[4] = { ProVertex(Vector3r(-1.0f, -1.0f, 0.0f)),
		ProVertex(Vector3r(0.0f, 1.0f, 0.0f)),
		ProVertex(Vector3r(1.0f, -1.0f, 0.0f)),
		ProVertex(Vector3r(0.0f, -1.0f, 1.0f))};

	int indices[12] = { 0, 1, 3,
						3, 1, 2,
						2, 1, 0,
						0, 2, 3 };

	mesh.AddVertices(vertices, indices, 12);

	shader.AddVertexShader("..\\..\\res\\shaders\\basicShader.vs");
	shader.AddFragmentShader("..\\..\\res\\shaders\\basicShader.fs");
	shader.Compile();
}

Real temp = 0.0f;
Matrix4 projectionM = Transform::GetProjectionMatrix(70.0f, 800.0f/600.0f, 0.1f, 100.0f);

void gameApp::update()
{
	temp += ProTime::getDelta();
	Real value = std::sin(temp);
	transform.setTranslation(value, 0.0f, -5.0f);
	transform.setRotation(0.0f, value * 5, 0.0f);
}

void gameApp::render()
{
	shader.Bind();
	shader.SetUniformMatrix4F("model", transform.getTransformMatrix().transpose());
	shader.SetUniformMatrix4F("projection", projectionM.transpose());

	mesh.Draw();
}

void gameApp::stop()
{
}

void gameApp::input()
{
}

