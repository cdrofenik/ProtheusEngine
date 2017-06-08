#include "physics\dynamics\RigidBody.h"

// system dependency
#include <math.h>

using namespace math;

namespace physics
{

	static inline void calculateTransformMatrix(Matrix3x4& transformMatrix, const Vector3r& pos,
		const Quarternion& orientation)
	{
		transformMatrix.m[0] = 1 - (2 * orientation.j * orientation.j + 2 * orientation.k * orientation.k);
		transformMatrix.m[1] = 2 * orientation.i * orientation.j + 2 * orientation.k * orientation.r;
		transformMatrix.m[2] = 2 * orientation.i * orientation.k - 2 * orientation.j * orientation.r;
		transformMatrix.m[3] = pos.x;

		transformMatrix.m[4] = 2 * orientation.i * orientation.j - 2 * orientation.k * orientation.r;
		transformMatrix.m[5] = 1 - (2 * orientation.i * orientation.i + 2 * orientation.k * orientation.k);
		transformMatrix.m[6] = 2 * orientation.j * orientation.k + 2 * orientation.i * orientation.r;
		transformMatrix.m[7] = pos.y;

		transformMatrix.m[8] = 2 * orientation.i * orientation.k + 2 * orientation.j * orientation.r;
		transformMatrix.m[9] = 2 * orientation.j * orientation.k - 2 * orientation.i * orientation.r;
		transformMatrix.m[10] = 1 - (2 * orientation.i * orientation.i + 2 * orientation.j * orientation.j);
		transformMatrix.m[11] = pos.z;
	}

	static inline void transformIntertiaTensor(Matrix3& iitWorld, const Quarternion& q,
		const Matrix3& iitBody, const Matrix3x4& rotMatrix)
	{
		Real t4 = rotMatrix.m[0] * iitBody.m[0] + rotMatrix.m[1] * iitBody.m[3] +
			rotMatrix.m[2] * iitBody.m[6];

		Real t9 = rotMatrix.m[0] * iitBody.m[1] + rotMatrix.m[1] * iitBody.m[4] +
			rotMatrix.m[2] * iitBody.m[7];

		Real t14 = rotMatrix.m[0] * iitBody.m[2] + rotMatrix.m[1] * iitBody.m[5] +
			rotMatrix.m[2] * iitBody.m[8];

		Real t28 = rotMatrix.m[4] * iitBody.m[0] + rotMatrix.m[5] * iitBody.m[3] +
			rotMatrix.m[6] * iitBody.m[6];

		Real t33 = rotMatrix.m[4] * iitBody.m[1] + rotMatrix.m[5] * iitBody.m[4] +
			rotMatrix.m[6] * iitBody.m[7];

		Real t38 = rotMatrix.m[4] * iitBody.m[2] + rotMatrix.m[5] * iitBody.m[5] +
			rotMatrix.m[6] * iitBody.m[8];

		Real t52 = rotMatrix.m[8] * iitBody.m[0] + rotMatrix.m[9] * iitBody.m[3] +
			rotMatrix.m[10] * iitBody.m[6];

		Real t57 = rotMatrix.m[8] * iitBody.m[1] + rotMatrix.m[9] * iitBody.m[4] +
			rotMatrix.m[10] * iitBody.m[7];

		Real t62 = rotMatrix.m[8] * iitBody.m[2] + rotMatrix.m[9] * iitBody.m[5] +
			rotMatrix.m[10] * iitBody.m[8];

		iitWorld.m[0] = t4 * rotMatrix.m[0] + t9 * rotMatrix.m[1] + t14 * rotMatrix.m[2];
		iitWorld.m[1] = t4 * rotMatrix.m[4] + t9 * rotMatrix.m[5] + t14 * rotMatrix.m[6];
		iitWorld.m[2] = t4 * rotMatrix.m[8] + t9 * rotMatrix.m[9] + t14 * rotMatrix.m[10];
		iitWorld.m[3] = t28 * rotMatrix.m[0] + t33 * rotMatrix.m[1] + t38 * rotMatrix.m[2];
		iitWorld.m[4] = t28 * rotMatrix.m[4] + t33 * rotMatrix.m[5] + t38 * rotMatrix.m[6];
		iitWorld.m[5] = t28 * rotMatrix.m[8] + t33 * rotMatrix.m[9] + t38 * rotMatrix.m[10];
		iitWorld.m[6] = t52 * rotMatrix.m[0] + t57 * rotMatrix.m[1] + t62 * rotMatrix.m[2];
		iitWorld.m[7] = t52 * rotMatrix.m[4] + t57 * rotMatrix.m[5] + t62 * rotMatrix.m[6];
		iitWorld.m[8] = t52 * rotMatrix.m[8] + t57 * rotMatrix.m[9] + t62 * rotMatrix.m[10];
	}

	#pragma region Setters/Getters
	
	void RigidBody::setInverseMass(const Real& imass)
	{
		m_inverseMass = imass;
	}

	Real RigidBody::getInverseMass() const
	{
		return m_inverseMass;
	}

	void RigidBody::setLinearDamping(const Real& linDamp)
	{
		m_linearDamping = linDamp;
	}

	Real RigidBody::getLinearDamping() const
	{
		return m_linearDamping;
	}

	void RigidBody::setAngularDamping(const Real& angDamp)
	{
		m_angularDamping = angDamp;
	}

	Real RigidBody::getAngularDamping() const
	{
		return m_angularDamping;
	}

	void RigidBody::setPosition(const Vector3r& pos)
	{
		m_position = pos;
	}

	Vector3r RigidBody::getPosition() const
	{
		return m_position;
	}

	void RigidBody::setVelocity(const Vector3r& vel)
	{
		m_velocity = vel;
	}

	Vector3r RigidBody::getVelocity() const
	{
		return m_velocity;
	}

	void RigidBody::setAcceleration(const Vector3r& acc)
	{
		m_acceleration = acc;
	}

	Vector3r RigidBody::getAcceleration() const
	{
		return m_acceleration;
	}

	void RigidBody::setRotation(const Vector3r& rot)
	{
		m_rotation = rot;
	}

	Vector3r RigidBody::getRotation() const
	{
		return m_rotation;
	}
	#pragma endregion

	void RigidBody::addForce(const Vector3r& force)
	{
		m_forceAccum += force;
		m_isAwake = true;
	}

	void RigidBody::addForceAtPoint(const Vector3r& force, const Vector3r& point)
	{
		Vector3r pt = point;
		pt -= m_position;

		m_forceAccum += force;
		m_torqueAccum += pt % force;

		m_isAwake = true;
	}

	void RigidBody::addForceAtBodyPoint(const Vector3r& force, const Vector3r& point)
	{
		Vector3r pt = getPointInWorldSpace(point);
		addForceAtPoint(force, pt);

		m_isAwake = true;
	}

	void RigidBody::setIntertiaTensor(const Matrix3& inertiaTensor)
	{
		m_inverseInertiaTensor = inertiaTensor.inverse();
	}

	void RigidBody::calculateDerivedData()
	{
		m_orientation.normalize();

		calculateTransformMatrix(m_transformMatrix, m_position, m_orientation);

		transformIntertiaTensor(m_inverseInertiaTensor, m_orientation, m_inverseInertiaTensor,
			m_transformMatrix);
	}

	Vector3r RigidBody::getPointInLocalSpace(const Vector3r& point) const
	{
		return m_transformMatrix.transformInverse(point);
	}

	Vector3r RigidBody::getPointInWorldSpace(const Vector3r& point) const
	{
		return m_transformMatrix.transform(point);
	}

	void RigidBody::integrate(Real duration)
	{
		if (m_inverseMass <= 0.0f) return;

		m_lastFrameAcceleration = m_acceleration;
		m_lastFrameAcceleration.addScaledVector(m_forceAccum, m_inverseMass);

		Vector3r angularAcceleration = m_inverseInertiaTensorWorld.transform(m_torqueAccum);

		m_velocity.addScaledVector(m_lastFrameAcceleration, duration);
		m_rotation.addScaledVector(angularAcceleration, duration);

		m_velocity *= powf(m_linearDamping, duration);
		m_rotation *= powf(m_angularDamping, duration);

		m_position.addScaledVector(m_velocity, duration);
		m_orientation.addScaledVector(m_rotation, duration);

		calculateDerivedData();

		clearAccum();
	}

	void RigidBody::clearAccum()
	{
		m_forceAccum = Vector3r();
		m_torqueAccum = Vector3r();
		//m_forceAccum;
		//m_torqueAccum;
	}

	bool RigidBody::isAwake() const
	{
		return m_isAwake;
	}

	bool RigidBody::isAsleep() const
	{
		return m_canSleep;
	}
}