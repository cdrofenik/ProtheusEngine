#pragma once

#include "core/math/Precision.hpp"

// system dependency
#include <math.h>
#include <vector>

namespace physics {

	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
	static const math::Real AABB_BUFFER_DATA[] = {
		-1.0f, -1.0f, -1.0f, // triangle 1 : begin
		-1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, // triangle 1 : end
		1.0f, 1.0f, -1.0f, // triangle 2 : begin
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f, // triangle 2 : end
		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f
	};

	math::Real* GenerateSphere(math::Real r, const int& lats, const int& longs) {
		int i, j;
		std::vector<math::Real> sphere_data = std::vector<math::Real>();
		for (i = 0; i <= lats; i++) {
			math::Real lat0 = DEF_PI * (-0.5 + (math::Real)(i - 1) / lats);
			math::Real z0 = sin(lat0);
			math::Real zr0 = cos(lat0);

			math::Real lat1 = DEF_PI * (-0.5 + (math::Real)i / lats);
			math::Real z1 = sin(lat1);
			math::Real zr1 = cos(lat1);

			for (j = 0; j <= longs; j++) {
				math::Real lng = 2 * DEF_PI * (math::Real)(j - 1) / longs;
				math::Real x = cos(lng);
				math::Real y = sin(lng);

				sphere_data.push_back(x * zr0, y * zr0, z0);
				sphere_data.push_back(x * zr1, y * zr1, z1);
			}
		}
	}
}