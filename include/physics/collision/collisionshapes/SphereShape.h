#ifndef SPHERESHAPE_H
#define SPHERESHAPE_H

#include "core/math/Vector3.hpp"

#include "CollisionShape.h"

namespace physics
{
	class SphereShape : public CollisionShape
	{
	public:
		SphereShape() : m_center(math::Vector3r()), m_radius(0.0) {}
		SphereShape(const math::Vector3r& centerPoint, const math::Real& radius) :
			m_center(centerPoint),
			m_radius(radius)
		{
			setType(CollisionShapeType::SPHERE_SHAPE);
		}
		SphereShape(const math::Vector3r& centerPoint, const math::Vector3r& halfSize) :
			m_center(centerPoint)
		{
			setType(CollisionShapeType::SPHERE_SHAPE);

			if (halfSize.x > halfSize.y)
				if (halfSize.x > halfSize.z)
					m_radius = halfSize.x;
				else
					m_radius = halfSize.z;
			else
				if (halfSize.y > halfSize.z)
					m_radius = halfSize.y;
				else
					m_radius = halfSize.z;
		}

		~SphereShape();

		virtual void getAabb(math::Vector3r& aabbMin, math::Vector3r& aabbMax) const {}

		void getBoundingSphere(math::Vector3r& center, math::Real& radius) const
		{
			center = m_center;
			radius = m_radius;
		}

		math::Real getRadius() const { return m_radius; }

	private:
		math::Vector3r m_center;
		math::Real m_radius;
	};
}

#endif