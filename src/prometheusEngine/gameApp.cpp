#include "gameApp.h"

#include "ProTime.h"
#include "ProResourceLoader.h"
#include "input\InputHandler.h"

#include <math.h>

#include "physics\collision\collisionshapes\BoxShape.h"

using namespace math;
using namespace physics;
using namespace input;

gameApp::gameApp()
{
}

gameApp::~gameApp()
{
}


RigidBody generateRigidBody(
	DiscreteDynamicsWorld* world,
	const Aabb& bodyAabb,
	const Vector3r& startPosition,
	ForceGenerator* forceGenerator,
	const CollisionShapeType& type,
	unsigned int& count)
{
	RigidBody rBody(10, startPosition, Vector3r(0.0, 0.0, 0.0), Vector3r(0.0, 0.0, 0.0));
	CollisionShape* shape = new BoxShape(rBody.getPosition(), bodyAabb.getAabbHalfSize());
	if (type == CollisionShapeType::SPHERE_SHAPE)
		shape = new SphereShape(rBody.getPosition(), bodyAabb.getAabbHalfSize());

	rBody.setAngularDamping(0.05f);
	rBody.setLinearDamping(0.011f);
	rBody.setCollisionShape(shape);

	world->addRigidBody(rBody, bodyAabb);
	world->addConstantForce(count, forceGenerator);
	count++;

	return rBody;
}

void initializeObjects(DiscreteDynamicsWorld* world, const Vector3r& minValues, const Vector3r& maxValues)
{
	unsigned int rigidBodyCount = 2;

	Vector3r Pos(0.0f, 0.0f, 0.0f);
	Vector3r veloPos(0, 0, 0);
	Vector3r accelPos(0, 0, 0);

	//drawableModelList.clear();
	int indexCounter = 2;

	Aabb bodyAabb = Aabb(
		Vector3r(minValues.x, minValues.y, minValues.z),
		Vector3r(maxValues.x, maxValues.y, maxValues.z)
	);

	Vector3r startPos1 = Vector3r(-0.9, 0.0f, 0.0f);
	unsigned int counter = 0;
	LinearPendulumForce* pForce = new
		LinearPendulumForce(startPos1, startPos1 +
			Vector3r(1.1f, 0.0f, 0.0f), 3);
	auto body = generateRigidBody(world,
		bodyAabb,
		startPos1,
		pForce,
		CollisionShapeType::BOX_SHAPE,
		counter);

	/*DrawableShape bodyShape;
	if (body.getCollisionShape()->getType() == CollisionShapeType::BOX_SHAPE) {
		bodyShape = Box(minValues, maxValues);
	}
	else if (body.getCollisionShape()->getType() == CollisionShapeType::SPHERE_SHAPE) {
		bodyShape = Sphere(minValues, maxValues);
	}
	drawableModelList.push_back(bodyShape);*/

	indexCounter++;
	Vector3r startPos2 = Vector3r(0.9, 0.0f, 0.0f);
	LinearPendulumForce* pForce2 = new
		LinearPendulumForce(startPos2, startPos2 +
			Vector3r(-1.1f, 0.0f, 0.0f), 3);
	body = generateRigidBody(world,
		bodyAabb,
		startPos2,
		pForce2,
		CollisionShapeType::SPHERE_SHAPE,
		counter);

	/*if (body.getCollisionShape()->getType() == CollisionShapeType::BOX_SHAPE) {
		bodyShape = Box(minValues, maxValues);
	}
	else if (body.getCollisionShape()->getType() == CollisionShapeType::SPHERE_SHAPE) {
		bodyShape = Sphere(minValues, maxValues);
	}
	drawableModelList.push_back(bodyShape);*/

	//Adding force generators
	world->setupForceRegistry();
}

void gameApp::start()
{
	camera = new ProCamera(Vector3r(0.0f, 0.0f, 0.0f),
		Vector3r(0.0f, 1.0f, 0.0f),
		Vector3r(0.0f, 0.0f, -1.0f));
	
	ObjectLoader obj;
	objLoader = obj.loadObject("..\\..\\res\\models\\advancedCube.obj");

	shader.AddVertexShader("..\\..\\res\\shaders\\basicShader.vs");
	shader.AddFragmentShader("..\\..\\res\\shaders\\basicShader.fs");
	shader.Compile();

	//m_discreteWorld = new DiscreteDynamicsWorld();
	//initializeObjects(m_discreteWorld, );
}

Real temp = 0.0f;
Matrix4 projectionM = Transform::projectionMatrix(70.0f, 800.0f/600.0f, 0.1f, 100.0f);

void gameApp::update()
{
	if (InputHandler::isKeyDown(32)) {
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

	objLoader.Draw();
}
	
void gameApp::stop()
{
}

void gameApp::input()
{
	camera->input();
}

