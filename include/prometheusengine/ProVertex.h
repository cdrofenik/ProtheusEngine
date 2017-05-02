#pragma once

#include "../include/core/math/Vector3.hpp"

struct ProVertex
{
public:

	math::Vector3r GetPosition() {
		return m_position;
	}

	void SetPosition(math::Real x, math::Real y, math::Real z) {
		m_position.x = x;
		m_position.y = y;
		m_position.z = z;
	}

	ProVertex(math::Vector3r vector) {
		m_position = vector;
	}


private:
	math::Vector3r m_position = math::Vector3r(0.0f, 0.0f, 0.0f);
};