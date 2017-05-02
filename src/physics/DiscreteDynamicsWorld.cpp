#include "physics\DiscreteDynamicsWorld.h"

#include "core\collections\AlignedArray.hpp"
#include "core/math/Vector3.hpp"
#include "core/math/Transform.hpp"

#include "physics\collision\collisionshapes\BoxShape.h"
#include "physics\collision\narrowphase\CollisionAlgorithm.h"

using namespace math;
using namespace collections;

namespace physics
{

	DiscreteDynamicsWorld::DiscreteDynamicsWorld()
	{
		m_pairManager = new PairManager();
		m_broadphase = new SweepAndPrune(m_pairManager); //Dbvt, UniformGrid, npSortAndSweep(m_pairManager)

		PUniformGrid* test = new PUniformGrid(50, Vector3r(0.5, 0.5, 0.5));

		numRigidBodies = 0;
	}

	DiscreteDynamicsWorld::~DiscreteDynamicsWorld()
	{
		delete m_broadphase;
		delete m_pairManager;
		m_registry.clear();
		m_rigidBodyList.clear();

		numRigidBodies = 0;
	}

	//Check if colliding return - collision pair info to pair manager if really colliding
	//Narrow phase + Generating Collisions
	void DiscreteDynamicsWorld::checkNarrowPhase()
	{
		unsigned int size = m_pairManager->getPotentialPairs().size();
		if (size > 0)
		{
			AlignedArray<PotentialPair> pairs = m_pairManager->getPotentialPairs();
			for (unsigned int i = 0; i < size; i++)
			{
				//Get pair
				CollisionObject* obj0 =& m_rigidBodyList.at(pairs.at(i).bodyIdA);
				CollisionObject* obj1 =& m_rigidBodyList.at(pairs.at(i).bodyIdB);

				//Process pair - Narrow phase
				CollisionInfo info;
				info.setCollisionObjects(obj0, obj1);
				if (CollisionAlgorithm::processCollision(obj0, obj1, info))
					m_pairManager->addCollisionPairInfo(info);
				else
					m_pairManager->removeCollisionPairInfo(info);
			}
		}
		
	}

	void DiscreteDynamicsWorld::stepSimulation(float _deltaTime)
	{
		int counter = 0;
		AlignedArray<AabbUpdateData> changedAabbList = AlignedArray<AabbUpdateData>();
		for (auto& body : m_rigidBodyList)
		{
			if (body.isAwake() && body.getInverseMass() > 0) {
				Vector3r oldPositiong = body.getPosition();
				body.integrate(_deltaTime);
				Vector3r moveVector = body.getPosition() - oldPositiong;

				Aabb updatedAabb;
				updatedAabb.m_minVec = m_aabbList.at(counter).m_minVec + moveVector;
				updatedAabb.m_maxVec = m_aabbList.at(counter).m_maxVec + moveVector;
				m_broadphase->update(AabbUpdateData(m_aabbList.at(counter), moveVector), counter);

				changedAabbList.push_back(AabbUpdateData(m_aabbList.at(counter), moveVector));
			}
			counter++;
		}

		//BROAD PHASE
		m_broadphase->getPotentialContacts(m_pairManager);

		//NARROW PHASE
		checkNarrowPhase();

		//Collision Resolve?


		//Updated aabb list
		for (int i = 0; i < changedAabbList.size(); i++)
		{
			auto currentDiff = changedAabbList[i];

			m_aabbList[i].m_maxVec = currentDiff.originalAabb.m_maxVec +
				currentDiff.directionDiff;
			m_aabbList[i].m_minVec = currentDiff.originalAabb.m_minVec +
				currentDiff.directionDiff;
		}
		m_registry.updateForces(_deltaTime);
	}

	void DiscreteDynamicsWorld::addRigidBody(const RigidBody& body, Aabb boundingVolume)
	{
		//Add rigid body to list
		m_rigidBodyList.push_back(body);
		m_aabbList.push_back(Aabb(body.getPosition() + boundingVolume.m_minVec,
			body.getPosition() + boundingVolume.m_maxVec));

		//Add aabb to broadPhase algorithm
		m_broadphase->insert(m_aabbList.at(numRigidBodies), numRigidBodies);

		numRigidBodies++;
	}

	void DiscreteDynamicsWorld::addConstantForce(const unsigned int& index, ForceGenerator* _generator)
	{
		IndexForces idxFrc;
		idxFrc.index = index;
		idxFrc.force = _generator;
		m_registeredForces.push_back(idxFrc);
	}

	void DiscreteDynamicsWorld::setupForceRegistry()
	{
		std::vector<RigidBody>::iterator iter;
		int counter = 0;
		for (int i = 0; i < m_registeredForces.size(); i++)
		{
			RigidBody* rb =& m_rigidBodyList.at(m_registeredForces.at(i).index);
			m_registry.add(rb, m_registeredForces.at(i).force);
		}
	}

	RigidBody DiscreteDynamicsWorld::getRigidBody(int _idx)
	{
		return m_rigidBodyList.at(_idx);
	}

}