#include "gameApp.h"

#include "utils\Time.h"
#include "input\InputHandler.h"

#include <math.h>

#include "physics\collision\collisionshapes\BoxShape.h"

#include "graphics\buffers\Buffer.h"
#include "graphics\buffers\IndexedBuffer.h"
#include "graphics\buffers\VertexArray.h"

using namespace math;
using namespace physics;
using namespace input;
using namespace graphics;
using namespace buffers;

gameApp::gameApp()
{
}

gameApp::~gameApp()
{
}


void generateRigidBody(DiscreteDynamicsWorld* world,
	const Aabb& bodyAabb,
	const Vector3r& startPosition)
{
	RigidBody rBody(10, startPosition, Vector3r(0.0, 0.0, 0.0), Vector3r(0.0, 0.0, 0.0));
	CollisionShape* shape = new BoxShape(rBody.getPosition(), bodyAabb.getAabbHalfSize());
	//if (type == CollisionShapeType::SPHERE_SHAPE)
	//	shape = new SphereShape(rBody.getPosition(), bodyAabb.getAabbHalfSize());

	rBody.setAngularDamping(0.05f);
	rBody.setLinearDamping(0.011f);
	rBody.setCollisionShape(shape);
	rBody.calculateDerivedData();

	world->addRigidBody(rBody, bodyAabb);
}

void setupPhysics(DiscreteDynamicsWorld* world, OBJLoader::Mesh mesh) {

	Vector3r min(5, 5, 5);
	Vector3r max(-1, -1, -1);
	for (size_t i = 0; i < mesh.positions.size(); i++)
	{
		if (mesh.positions[i].x > max.x) {
			max.x = mesh.positions[i].x;
		}
		if (mesh.positions[i].y > max.y) {
			max.y = mesh.positions[i].y;
		}
		if (mesh.positions[i].z > max.z) {
			max.z = mesh.positions[i].z;
		}

		if (mesh.positions[i].x < min.x) {
			min.x = mesh.positions[i].x;
		}
		if (mesh.positions[i].y < min.y) {
			min.y = mesh.positions[i].y;
		}
		if (mesh.positions[i].z < min.z) {
			min.z = mesh.positions[i].z;
		}
	}

	Aabb bodyAabb = Aabb(min, max);
	
	{
		Vector3r startPosition = Vector3r(0.0f, 0.0f, 0.0f);
		generateRigidBody(world, bodyAabb, startPosition);
	}
	{
		Vector3r startPosition = Vector3r(0.0f, 4.0f, -5.0f);
		generateRigidBody(world, bodyAabb, startPosition);
	}

	GravityForce* gf = new GravityForce(Vector3r(0.0f, -0.1f, 0.0f));
	world->addConstantForce(1, gf);

	//Adding force generators
	world->setupForceRegistry();
}

void gameApp::start()
{
	camera = new Camera(Vector3r(0.0f, 0.5f, 2.0f),
		Vector3r(0.0f, 1.0f, 0.0f),
		Vector3r(0.0f, 0.0f, -1.0f));

	texture.loadTexture("resources\\textures\\wall.jpg");

	shader.addVertexShader("resources\\shaders\\basicShader.vs");
	shader.addFragmentShader("resources\\shaders\\basicShader.fs");
	shader.compile();

	OBJLoader loader;
	loadedMesh = loader.loadObject("resources\\models\\advancedCube.obj");


#pragma region VA setting up
	Buffer* positionsBuffer = new Buffer(loadedMesh.positions, loadedMesh.positions.size(), 3);
	Buffer* normalBuffer = new Buffer(loadedMesh.normals, loadedMesh.normals.size(), 3);
	Buffer* textureBuffer = new Buffer(loadedMesh.textureCoordinates, loadedMesh.textureCoordinates.size(), 2);
	
	VertexArray va;
	va.addBuffer(positionsBuffer, 0);
	va.addBuffer(normalBuffer, 1);
	va.addBuffer(textureBuffer, 2);

	va.bind();
	IndexedBuffer idBuffer(loadedMesh.indices, loadedMesh.indices.size());
	va.unbind();

	//TODO: Add buffer manager


	//loadedMesh.rd.vao = va.
#pragma endregion

	//TODO load empty plane

	m_discreteWorld = new DiscreteDynamicsWorld();
	setupPhysics(m_discreteWorld, loadedMesh);
}

//double temp = 0.0f;
Matrix4 projectionM = Transform::projectionMatrix(70.0f, 800.0f/600.0f, 0.1f, 100.0f).transpose();

void gameApp::update()
{
	if (isPaused)
		return;

	m_discreteWorld->stepSimulation(Time::getDelta());

	//temp += Time::getDelta();
	//Real value = static_cast<Real>(std::sin(temp));
	//transform.setTranslation(value, 0.0f, -5.0f);
	//transform.setScale(0.5f, 0.5f, 0.5f);
	//transform.setRotation(0.0f, value * 5, 0.0f);
}

void gameApp::render()
{
	for (unsigned int i = 0; i < 2; i++)
	{
		auto rigidBdy = m_discreteWorld->getRigidBody(i);
		shader.bind();
		texture.bind();
		shader.setUniformMatrix4F("model", Matrix4(rigidBdy.getTransformMatrix()).transpose());
		shader.setUniformMatrix4F("projection", projectionM);
		shader.setUniformMatrix4F("view", camera->GetCameraMatrix().transpose());

		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		//glBindVertexArray(this->vao);
		//glEnableVertexAttribArray(0); // Position
		//glEnableVertexAttribArray(1); // Normal
		//glEnableVertexAttribArray(2); // Texture
		//glDrawElements(GL_TRIANGLES, this->size, GL_UNSIGNED_INT, 0);
		//glDisableVertexArrayAttrib(this->vao, 0);
		//glDisableVertexArrayAttrib(this->vao, 1);
		//glDisableVertexArrayAttrib(this->vao, 2);
		//glBindVertexArray(0);
		//loadedMesh.rd.Draw();
	}
}
	
void gameApp::stop()
{
}

void gameApp::input()
{
	camera->input();

	if (InputHandler::isKeyDown(32)) {
		isPaused = !isPaused;
	}
}

