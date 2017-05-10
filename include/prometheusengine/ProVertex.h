#pragma once

#include "core/math/Vector2.hpp"
#include "core/math/Vector3.hpp"

struct ProVertex
{
	math::Vector3r position = math::Vector3r(0.0f, 0.0f, 0.0f);
	math::Vector3r normal = math::Vector3r(0.0f, 0.0f, 0.0f);
	math::Vector2r textureCoordinates = math::Vector2r(0.0f, 0.0f);

	ProVertex(math::Vector3r pos, math::Vector3r norm, math::Vector2r texCoord) :
		position(pos),
		normal(norm),
		textureCoordinates(texCoord)
	{}
};