#pragma once

#include "core\math\ProTransform.hpp"

#include "ProVertex.h"
#include "ProMesh.h"
#include "ProShader.h"


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
	ProTransform transform;
};

