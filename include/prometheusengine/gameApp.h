#pragma once

#include "core\math\Transform.hpp"

#include "ProVertex.h"
#include "ProMesh.h"
#include "ProShader.h"
#include "ProCamera.h"


class gameApp
{
public:
	gameApp();
	~gameApp();

	void start();
	void render();
	void stop();
	void input();
	void update();

private:
	ProMesh mesh;
	ProShader shader;
	math::Transform transform;
	ProCamera* camera;

	bool isPaused = false;
};

