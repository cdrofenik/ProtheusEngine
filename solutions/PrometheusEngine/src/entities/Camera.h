#pragma once

#include "core\math\Matrix4.hpp"
#include "..\graphics\Window.h"

class Camera
{
public:
	Camera(math::Vector3r pos, math::Vector3r up, math::Vector3r forward);
	~Camera();

	void input();
	math::Matrix4 GetCameraMatrix();

private:
	math::Vector3r m_pos;
	math::Vector3r m_up;
	math::Vector3r m_front;
	math::Vector3r m_right;
	math::Real m_yaw;
	math::Real m_pitch;

	void rotate(math::Real xPos, math::Real yPos, const bool& constrainPitch);
	void move(math::Vector3r direction, math::Real amount);
	void updateInternalValues();
};