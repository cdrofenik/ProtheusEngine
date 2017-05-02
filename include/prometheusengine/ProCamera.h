#pragma once

#include "core\math\Matrix4.hpp"

class ProCamera
{
public:
	ProCamera(math::Vector3r pos, math::Vector3r up, math::Vector3r forward);
	~ProCamera();

	math::Matrix4 GetCameraMatrix();
	
	void input();


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
	void evaluateMouseMove();
};