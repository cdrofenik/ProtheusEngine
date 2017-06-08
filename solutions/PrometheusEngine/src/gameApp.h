#pragma once

#include "core\math\Transform.hpp"

#include "physics\DiscreteDynamicsWorld.h"

#include "entities\Camera.h"
#include "utils\OBJLoader.h"
#include "graphics\Shader.h"
#include "graphics\Texture.h"


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
	graphics::Shader shader;
	math::Transform transform;
	Camera* camera;
	OBJLoader::Mesh loadedMesh;
	graphics::Texture texture;

	physics::DiscreteDynamicsWorld* m_discreteWorld;

	bool isPaused = false;
};

