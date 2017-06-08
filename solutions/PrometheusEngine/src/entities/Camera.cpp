#include "Camera.h"

#include "core\math\Transform.hpp"

#include "..\input\InputHandler.h"
#include "..\utils\Time.h"

#include <iostream>

using namespace math;
using namespace input;

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

Camera::Camera(Vector3r pos, Vector3r up, Vector3r front) :
	m_pos(pos), m_up(up), m_front(front), m_yaw(YAW), m_pitch(PITCH)
{
	updateInternalValues();
}

Camera::~Camera()
{
}

Matrix4 Camera::GetCameraMatrix()
{
	Matrix4 result = Transform::lookAtMatrix(this->m_pos, this->m_pos + this->m_front, this->m_up);
	return result;
}

void Camera::input()
{
	if (InputHandler::isKeyDown(W_KEY))
		move(this->m_front, SPEED * Time::getDelta());
	if (InputHandler::isKeyDown(S_KEY))
		move(this->m_front * -1.0f, SPEED * Time::getDelta());
	if (InputHandler::isKeyDown(A_KEY))
		move(this->m_right * -1.0f, SPEED * Time::getDelta());
	if (InputHandler::isKeyDown(D_KEY)) {
		move(this->m_right, SPEED * Time::getDelta());
	}

	Real yOffset;
	Real xOffset;

	if(InputHandler::getMousePositionChanged(xOffset, yOffset))
		rotate(xOffset, yOffset, true);
}

void Camera::move(Vector3r direction, Real amount)
{
	m_pos += direction * amount;
}

void Camera::rotate(Real xoffset, Real yoffset, const bool& constrainPitch)
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

void Camera::updateInternalValues()
{
	Vector3r front;
	front.x = cos(TO_RADIAN(this->m_yaw)) * cos(TO_RADIAN(this->m_pitch));
	front.y = sin(TO_RADIAN(this->m_pitch));
	front.z = sin(TO_RADIAN(this->m_yaw)) * cos(TO_RADIAN(this->m_pitch));
	this->m_front = front.normalize();

	// Also re-calculate the Right and Up vector
	this->m_right = (this->m_front % WORLD_UP_VECTOR).normalize();
	this->m_up = (this->m_right % this->m_front).normalize();
}
