#ifndef COLLISIONSHAPE_H
#define COLLISIONSHAPE_H

#include "core/math/Precision.hpp"
#include "core/math/Vector3.hpp"

namespace physics {

	enum CollisionShapeType
	{
		BOX_SHAPE,
		SPHERE_SHAPE,
		CONVEX_SHAPE,
		PLANE_SHAPE
	};

	class CollisionShape
	{
	public:
		CollisionShape() : m_margin(0.0), m_scale(1.0), m_type(1) {}
		~CollisionShape() {}

		void setMargin(const math::Real& margin) { m_margin = margin; }
		math::Real getMargin() const { return m_margin; }

		void setScale(const math::Real& scale) { m_scale = scale; }
		math::Real getScale() const { return m_scale; }

		void setType(const int& type) { m_type = type; }
		int getType() const { return m_type; }

		virtual void getAabb(math::Vector3r& aabbMin, math::Vector3r& aabbMax) const = 0;
		virtual void getBoundingSphere(math::Vector3r& center, math::Real& radius) const {}

	protected:
		math::Real m_margin;
		math::Real m_scale;
		int m_type;
	};
}
#endif