#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "core\math\Matrix3x4.hpp"

#include "physics\MotionState.h"

#include "physics\collision\CollisionObject.h"

namespace physics {

	class RigidBody : public CollisionObject
	{
	public:
		RigidBody(const float& mass, const math::Vector3r& position,
			const math::Vector3r& velocity, const math::Vector3r& acceleration) :
			m_inverseMass(mass),
			m_position(position),
			m_velocity(velocity),
			m_acceleration(acceleration) {}

		~RigidBody() {}

	protected:
		math::Real m_inverseMass;
		math::Real m_linearDamping;
		math::Real m_angularDamping;

		math::Vector3r m_position;
		math::Vector3r m_velocity;
		math::Vector3r m_acceleration;

		math::Vector3r m_rotation;
		math::Quarternion m_orientation;

		math::Matrix3 m_inverseInertiaTensor;
		math::Matrix3 m_inverseInertiaTensorWorld;

		math::Vector3r m_forceAccum;
		math::Vector3r m_torqueAccum;

		math::Vector3r m_lastFrameAcceleration;

		bool m_isAwake;
		bool m_canSleep;

	public:
		#pragma region Setters/Getters

		void setInverseMass(const math::Real& imass);
		math::Real getInverseMass() const;

		void setLinearDamping(const math::Real& linDamp);
		math::Real getLinearDamping() const;

		void setAngularDamping(const math::Real& angDamp);
		math::Real getAngularDamping() const;

		void setPosition(const math::Vector3r& pos);
		math::Vector3r getPosition() const;

		void setVelocity(const math::Vector3r& vel);
		math::Vector3r getVelocity() const;

		void setAcceleration(const math::Vector3r& acc);
		math::Vector3r getAcceleration() const;

		void setRotation(const math::Vector3r& rot);
		math::Vector3r getRotation() const;

		void setOrientation(const math::Quarternion& q);
		void setOrientation(const math::Real& r, const math::Real& i, const math::Real& j, const math::Real& k);
		math::Quarternion getOrientation() const;

		#pragma endregion

		void integrate(math::Real duration);

		void addForce(const math::Vector3r& force);

		void addForceAtPoint(const math::Vector3r& force, const math::Vector3r& point);

		void addForceAtBodyPoint(const math::Vector3r& force, const math::Vector3r& point);

		void setIntertiaTensor(const math::Matrix3& inertiaTensor);

		math::Vector3r getPointInLocalSpace(const math::Vector3r& point) const;

		math::Vector3r getPointInWorldSpace(const math::Vector3r& point) const;

		void calculateDerivedData();

		void clearAccum();

		bool isAwake() const;

		bool isAsleep() const;
	};

}
#endif