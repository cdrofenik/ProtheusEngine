#include "ProCamera.h"

#include "core\math\Transform.hpp"

#include "ProInputHandler.h"
#include "ProTime.h"

#include <iostream>

static const int W_KEY = 87;
static const int S_KEY = 83;
static const int A_KEY = 65;
static const int D_KEY = 68;

static const Vector3r WORLD_UP_VECTOR(0.0f, 1.0f, 0.0f);

const Real YAW = -90.0f;
const Real PITCH = 0.0f;
const Real SPEED = 3.0f;
const Real SENSITIVTY = 0.1f;
const Real ZOOM = 45.0f;

ProCamera::ProCamera(Vector3r pos, Vector3r up, Vector3r front) :
	m_pos(pos), m_up(up), m_front(front), m_yaw(YAW), m_pitch(PITCH)
{
	updateInternalValues();
}

ProCamera::~ProCamera()
{
}

Matrix4 ProCamera::GetCameraMatrix()
{
	Matrix4 result = Transform::lookAtMatrix(this->m_pos, this->m_pos + this->m_front, this->m_up);
	return result;
}

void ProCamera::input()
{
	if (ProInputHandler::isKeyDown(W_KEY))
		move(this->m_front, SPEED * ProTime::getDelta());
	if (ProInputHandler::isKeyDown(S_KEY))
		move(this->m_front * -1.0f, SPEED * ProTime::getDelta());
	if (ProInputHandler::isKeyDown(A_KEY))
		move(this->m_right * -1.0f, SPEED * ProTime::getDelta());
	if (ProInputHandler::isKeyDown(D_KEY)) {
		move(this->m_right, SPEED * ProTime::getDelta());
	}

	evaluateMouseMove();
}

void ProCamera::evaluateMouseMove()
{
	Real xOffset;
	Real yOffset;

	if (ProInputHandler::getMousePositionChanged(xOffset, yOffset))
		rotate(xOffset, yOffset, true);
	
}

void ProCamera::move(Vector3r direction, Real amount)
{
	m_pos += direction * amount;
}

void ProCamera::rotate(Real xoffset, Real yoffset, const bool& constrainPitch)
{
	xoffset *= SENSITIVTY;
	yoffset *= SENSITIVTY;

	this->m_yaw += xoffset;
	this->m_pitch += yoffset;

	if (constrainPitch)
	{
		if (this->m_pitch > 89.0f)
			this->m_pitch = 89.0f;
		if (this->m_pitch < -89.0f)
			this->m_pitch = -89.0f;
	}

	updateInternalValues();
}

void ProCamera::updateInternalValues()
{
	Vector3r front;
	front.x = cos(ToRadian(this->m_yaw)) * cos(ToRadian(this->m_pitch));
	front.y = sin(ToRadian(this->m_pitch));
	front.z = sin(ToRadian(this->m_yaw)) * cos(ToRadian(this->m_pitch));
	this->m_front = front.normalize();

	// Also re-calculate the Right and Up vector
	this->m_right = (this->m_front % WORLD_UP_VECTOR).normalize();
	this->m_up = (this->m_right % this->m_front).normalize();
}
