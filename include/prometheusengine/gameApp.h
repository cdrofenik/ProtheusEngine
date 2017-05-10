#pragma once

#include "core\math\Transform.hpp"

#include "ProVertex.h"
#include "ProShader.h"
#include "ProCamera.h"
#include "ObjectLoader.h"

#include "physics\DiscreteDynamicsWorld.h"


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
	ProShader shader;
	math::Transform transform;
	ProCamera* camera;
	ObjectLoader::LoadedObject objLoader;

	physics::DiscreteDynamicsWorld* m_discreteWorld;

	bool isPaused = false;
};

