#ifndef BOXSHAPE_H
#define BOXSHAPE_H

#include "core/math/Vector3.hpp"

#include "CollisionShape.h"

namespace physics
{
	class BoxShape : public CollisionShape
	{
	public:
		math::Vector3r center;
		math::Vector3r halfSize;

		BoxShape() : center(math::Vector3r()), halfSize(math::Vector3r()) {}
		BoxShape(const math::Vector3r& centerPoint, const math::Vector3r& halfSpaces) :
			center(centerPoint),
			halfSize(halfSpaces)
		{
			setType(CollisionShapeType::BOX_SHAPE);
		}
		~BoxShape() {}

		virtual void getAabb(math::Vector3r& aabbMin, math::Vector3r& aabbMax) const
		{
			aabbMin = center - halfSize;
			aabbMax = center + halfSize;
		}

		//Calculates closest point on AABB box
		void closestPoint(const math::Vector3r& point, math::Vector3r& closestPoint) const
		{
			for (unsigned int i = 0; i < 3; i++)
			{
				math::Real value = point.getValue(i);
				if (value < -halfSize.getValue(i))
					value = -halfSize.getValue(i);
				if (value > halfSize.getValue(i))
					value = halfSize.getValue(i);
				closestPoint.setValue(i, value);
			}
		}
	};
}

#endif