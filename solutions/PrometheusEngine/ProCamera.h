#pragma once

#include "core\math\Matrix4.hpp"

class ProCamera
{
public:
	ProCamera(Vector3r pos, Vector3r up, Vector3r forward);
	~ProCamera();

	Matrix4 GetCameraMatrix();
	
	void input();


private:
	Vector3r m_pos;
	Vector3r m_up;
	Vector3r m_front;
	Vector3r m_right;
	Real m_yaw;
	Real m_pitch;

	void rotate(Real xPos, Real yPos, const bool& constrainPitch);
	void move(Vector3r direction, Real amount);
	void updateInternalValues();
	void evaluateMouseMove();
};