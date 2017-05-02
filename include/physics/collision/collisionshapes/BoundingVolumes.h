#ifndef BOUNDINGVOLUMES_H
#define BOUNDINGVOLUMES_H

#include "core/math/Vector3.hpp"

namespace physics {

	struct Sphere {
		math::Vector3r center;
		math::Real radius;

		Sphere(const math::Vector3r& c = math::Vector3r(), const math::Real& r = 1.0f) :
			center(c),
			radius(r) {}

		math::Real getMax(const int& axis) const {
			switch (axis)
			{
			case 0:
				return center.x + radius;
			case 1:
				return center.y + radius;
			case 2:
				return center.z + radius;
			default:
				return REAL_MAX;
			}
		}

		math::Real getMin(const int& axis) const {
			switch (axis)
			{
			case 0:
				return center.x - radius;
			case 1:
				return center.y - radius;
			case 2:
				return center.z - radius;
			default:
				return REAL_MAX;
			}
		}

	};

	struct Aabb {

	public:
		//float m_min[3];
		math::Vector3r m_minVec;

		//float m_max[3];
		math::Vector3r m_maxVec;

		Aabb() {
			m_minVec = math::Vector3r(0, 0, 0);
			m_maxVec = math::Vector3r(0, 0, 0);
		}

		Aabb(const math::Vector3r& minValues, const math::Vector3r& maxValues) : m_minVec(minValues),
			m_maxVec(maxValues) {}

		math::Real getSize() const {
			return (m_maxVec.x - m_minVec.x) * (m_maxVec.y - m_minVec.y) * (m_maxVec.z - m_minVec.z);
		}

		bool contains(const Aabb& volume) const {
			return (m_minVec.x < volume.m_minVec.x &&
				m_minVec.y < volume.m_minVec.y &&
				m_minVec.z < volume.m_minVec.z &&
				m_maxVec.x > volume.m_maxVec.x &&
				m_maxVec.y > volume.m_maxVec.y &&
				m_maxVec.z > volume.m_maxVec.z);
		}

		bool isEqual(const Aabb& volume) const {
			return (m_minVec.x == volume.m_minVec.x &&
				m_minVec.y == volume.m_minVec.y &&
				m_minVec.z == volume.m_minVec.z &&
				m_maxVec.x == volume.m_maxVec.x &&
				m_maxVec.y == volume.m_maxVec.y &&
				m_maxVec.z == volume.m_maxVec.z);
		}

		math::Vector3r getCenter() const {
			return math::Vector3r((m_minVec.x + m_maxVec.x) / 2, (m_minVec.y + m_maxVec.y) / 2,
				(m_minVec.y + m_maxVec.y) / 2);
		}

		math::Vector3r getTopLeft() const {
			return math::Vector3r(m_minVec.x, m_maxVec.y, m_minVec.z);
		}

		math::Vector3r getAabbSize() const {
			return m_maxVec - m_minVec;
		}

		math::Vector3r getAabbHalfSize() const {
			return math::Vector3r(
				(m_maxVec.x - m_minVec.x) / 2,
				(m_maxVec.y - m_minVec.y) / 2,
				(m_maxVec.z - m_minVec.z) / 2);
		}

		Sphere getBoundingSphere() const
		{
			return Sphere();
		}
	};

	struct AabbUpdateData
	{
		Aabb originalAabb;
		math::Vector3r directionDiff;

		AabbUpdateData(Aabb a, math::Vector3r b) :
			originalAabb(a),
			directionDiff(b) {}
	};

	inline bool npTestAabbAabb(const Aabb& first, const Aabb& second)
	{
		bool overlap = true;
		overlap = (first.m_minVec.x > second.m_maxVec.x || first.m_maxVec.x < second.m_minVec.x) ? false : overlap;
		overlap = (first.m_minVec.z > second.m_maxVec.z || first.m_maxVec.z < second.m_minVec.z) ? false : overlap;
		overlap = (first.m_minVec.y > second.m_maxVec.y || first.m_maxVec.y < second.m_minVec.y) ? false : overlap;
		return overlap;
	}

	__forceinline void npMergeAabbAabb(const Aabb& first, const Aabb& second, Aabb& result)
	{
		result.m_minVec.x = (first.m_minVec.x < second.m_minVec.x) ? first.m_minVec.x : second.m_minVec.x;
		result.m_minVec.y = (first.m_minVec.y < second.m_minVec.y) ? first.m_minVec.y : second.m_minVec.y;
		result.m_minVec.z = (first.m_minVec.z < second.m_minVec.z) ? first.m_minVec.z : second.m_minVec.z;

		result.m_maxVec.x = (first.m_maxVec.x > second.m_maxVec.x) ? first.m_maxVec.x : second.m_maxVec.x;
		result.m_maxVec.y = (first.m_maxVec.y > second.m_maxVec.y) ? first.m_maxVec.y : second.m_maxVec.y;
		result.m_maxVec.z = (first.m_maxVec.z > second.m_maxVec.z) ? first.m_maxVec.z : second.m_maxVec.z;
	}

	__forceinline math::Real npChangeInSurfaceAabbAabb(const Aabb& original, const Aabb& newElement)
	{
		Aabb newElementCopy;
		npMergeAabbAabb(original, newElement, newElementCopy);

		return newElementCopy.getSize() - original.getSize();
	}

	__forceinline math::Real npProximityAabbAabb(const Aabb& a, const Aabb& b)
	{
		math::Vector3r d = (a.m_minVec + a.m_maxVec) - (b.m_minVec + b.m_maxVec);
		return fabsf(d.x) + fabsf(d.y) + fabsf(d.z);
	}
}

#endif