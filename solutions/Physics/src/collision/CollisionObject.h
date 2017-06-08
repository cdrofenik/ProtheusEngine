#ifndef COLLISIONBODY_H
#define COLLISIONBODY_H

#include "core/math/Matrix3x4.hpp"
#include "collisionshapes\CollisionShape.h"

namespace physics {

	class CollisionObject
	{
	public:
		CollisionObject() {}
		~CollisionObject() {}

		void setCollisionShape(CollisionShape* _shape);
		CollisionShape* getCollisionShape() const;

		void setWorldPositiong(math::Vector3r _position);
		math::Vector3r getWorldPosition() const;

		void setTransformMatrix(const math::Matrix3x4& matrix);
		math::Matrix3x4 getTransformMatrix() const;

	protected:
		math::Vector3r m_worldPosition;
		math::Matrix3x4 m_transformMatrix;
		CollisionShape* m_collisionShape;
	};
}
#endif