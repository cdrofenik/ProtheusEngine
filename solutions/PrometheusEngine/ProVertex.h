#pragma once

#include "../include/core/math/Vector3.hpp"

struct ProVertex
{
public:
	static const int SIZE = 3;

	Vector3r GetPosition() {
		return m_position;
	}

	void SetPosition(Real x, Real y, Real z) {
		m_position.x = x;
		m_position.y = y;
		m_position.z = z;
	}

	ProVertex(Vector3r vector) {
		m_position = vector;
	}


private:
	Vector3r m_position = Vector3r(0.0f, 0.0f, 0.0f);
};