#pragma once

#include "core\math\Matrix4.hpp"

class ProCamera
{
public:
	ProCamera();
	~ProCamera();

	Matrix4 GetCameraMatrix();

};

