#include "physics\dynamics\Particle.h"

#include <assert.h>

using namespace math;

namespace physics {

	void Particle::integrate(Real duration) {
		if (m_inverseMass <= 0.0f) return;

		assert(duration > 0.0f);

		//Update linear position
		m_position.addScaledVector(m_velocity, duration);

		//Update acceleration
		Vector3r resultingAcc = m_acceleration;
		resultingAcc.addScaledVector(m_forceAccum, duration);

		//Update velocity
		m_velocity.addScaledVector(resultingAcc, duration);

		//Impose drag
		m_velocity *= powf(m_dampening, duration);

		clearAccum();
	}

	void Particle::addForce(const Vector3r& force) {
		m_forceAccum += force;
	}

	void Particle::clearAccum() {
		m_forceAccum = Vector3r(0, 0, 0);
	}
}