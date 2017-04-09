#pragma once

#include "../include/core/math/ProVector3.hpp"

struct ProVertex
{
public:
	static const int SIZE = 3;

	ProVector3r GetPosition() {
		return m_position;
	}

	void SetPosition(ProReal x, ProReal y, ProReal z) {
		m_position.x = x;
		m_position.y = y;
		m_position.z = z;
	}

	ProVertex(ProVector3r vector) {
		m_position = vector;
	}


private:
	ProVector3r m_position = ProVector3r(0.0f, 0.0f, 0.0f);
};