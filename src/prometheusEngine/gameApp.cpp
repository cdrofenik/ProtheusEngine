#include "gameApp.h"

#include "ProTime.h"
#include "ProResourceLoader.h"
#include "ProInputHandler.h"

#include <math.h>

using namespace math;

gameApp::gameApp()
{
}


gameApp::~gameApp()
{
}

void gameApp::start()
{
	camera = new ProCamera(Vector3r(0.0f, 0.0f, 0.0f),
		Vector3r(0.0f, 1.0f, 0.0f),
		Vector3r(0.0f, 0.0f, -1.0f));

	mesh.Init();
	ProResourceLoader::GetMeshFromFile("..\\..\\res\\models\\basicCube.obj", mesh);
	
	shader.AddVertexShader("..\\..\\res\\shaders\\basicShader.vs");
	shader.AddFragmentShader("..\\..\\res\\shaders\\basicShader.fs");
	shader.Compile();
}

Real temp = 0.0f;
Matrix4 projectionM = Transform::projectionMatrix(70.0f, 800.0f/600.0f, 0.1f, 100.0f);

void gameApp::update()
{
	if (ProInputHandler::isKeyDown(32)) {
		isPaused = !isPaused;
	}

	if (isPaused)
		return;

	temp += ProTime::getDelta();
	Real value = std::sin(temp);
	transform.setTranslation(value, 0.0f, -5.0f);
	transform.setScale(0.5f, 0.5f, 0.5f);
	//transform.setRotation(0.0f, value * 5, 0.0f);
}

void gameApp::render()
{
	shader.Bind();
	shader.SetUniformMatrix4F("model", transform.getTransformMatrix().transpose());
	shader.SetUniformMatrix4F("projection", projectionM.transpose());
	shader.SetUniformMatrix4F("view", camera->GetCameraMatrix().transpose());

	mesh.Draw();
}
	
void gameApp::stop()
{
}

void gameApp::input()
{
	camera->input();
}

