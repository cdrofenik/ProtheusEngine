#include "physics\collision\CollisionObject.h"

using namespace math;

namespace physics
{
	void CollisionObject::setCollisionShape(CollisionShape* _shape)
	{
		m_collisionShape = _shape;
	}

	CollisionShape* CollisionObject::getCollisionShape() const
	{ 
		return m_collisionShape;
	}

	void CollisionObject::setWorldPositiong(math::Vector3r _position)
	{
		m_worldPosition = _position;
	}

	math::Vector3r CollisionObject::getWorldPosition() const 
	{ 
		return math::Vector3r(m_transformMatrix.m[3], m_transformMatrix.m[7], m_transformMatrix.m[11]);
	}

	void CollisionObject::setTransformMatrix(const Matrix3x4& matrix)
	{
		m_transformMatrix = matrix;
	}

	Matrix3x4 CollisionObject::getTransformMatrix() const
	{
		return m_transformMatrix;
	}
}