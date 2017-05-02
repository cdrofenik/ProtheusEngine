#ifndef MOTIONSTATE_H
#define MOTIONSTATE_H

#include "core/math/Matrix4.hpp"

namespace physics
{
	class MotionState
	{
	public:
		MotionState(math::Matrix4 _startingState) : m_stateMarix(_startingState) {}
		~MotionState() {}

		math::Matrix4 GetStateMatrix4() { return m_stateMarix; }

		math::Vector3r GetPosition() { return math::Vector3r(m_stateMarix.m[3], m_stateMarix.m[7], m_stateMarix.m[11]); }

		void ChangePosition(math::Vector3r _newPosition)
		{
			m_stateMarix.m[3] = _newPosition.x;
			m_stateMarix.m[7] = _newPosition.y;
			m_stateMarix.m[11] = _newPosition.z;
		}

	private:
		math::Matrix4 m_stateMarix;
	};
}

#endif