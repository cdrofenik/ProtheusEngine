#ifndef COLLISIONALGORITHM_H
#define COLLISIONALGORITHM_H

#include "physics\collision\CollisionObject.h"

namespace physics {

	struct CollisionInfo
	{
	public:
		math::Vector3r contactPoint;
		math::Vector3r contactNormal;
		math::Real penetration;

		void setCollisionObjects(CollisionObject* object0, CollisionObject* object1) {
			obj0 = object0;
			obj1 = object1;
		}

	private:
		CollisionObject* obj0;
		CollisionObject* obj1;
	};

	class CollisionAlgorithm
	{
	public:
		static int processCollision(CollisionObject* obj0, CollisionObject* obj1, CollisionInfo& cInfo);
	};
}
#endif