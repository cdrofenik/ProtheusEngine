#ifndef DISCRETEWORLD_H
#define DISCRETEWORLD_H

#include "ForceGenerator.h"

#include "physics\collision\collisionshapes\BoundingVolumes.h"
#include "physics\dynamics\Particle.h"
#include "physics\dynamics\RigidBody.h"
#include "physics\collision\broadphase\Dbvt.h"
#include "physics\collision\broadphase\SweepAndPrune.h"
#include "physics\collision\broadphase\UniformGrid.h"
#include "physics\collision\broadphase\PUniformGrid.h"

#include <vector>

namespace physics {

	class DiscreteDynamicsWorld
	{
	public:
		DiscreteDynamicsWorld();
		~DiscreteDynamicsWorld();

		void stepSimulation(float _deltaTime);

		void addRigidBody(const RigidBody& body, Aabb boundingVolume);
		void addConstantForce(const unsigned int& index, ForceGenerator* _generator);
		void setupForceRegistry();

		RigidBody getRigidBody(int _idx);

	private:
		std::vector<RigidBody> m_rigidBodyList = std::vector<RigidBody>();
		std::vector<Aabb> m_aabbList = std::vector<Aabb>();
		int numRigidBodies;

		ForceRegistry m_registry;
		collections::AlignedArray<IndexForces> m_registeredForces = collections::AlignedArray<IndexForces>();


		//Pair Manager
		PairManager* m_pairManager;

		IBroadPhase* m_broadphase;

		void checkNarrowPhase();
	};
}
#endif