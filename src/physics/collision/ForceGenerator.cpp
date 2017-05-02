#include "physics\ForceGenerator.h"

#include <algorithm>

using namespace math;

namespace physics {

	//----- ParticleGravity

	void ParticleGravity::updateForce(Particle* particle, Real duration)
	{
		if (particle->m_inverseMass == 0) return;

		math::Vector3r val = m_gravity * particle->m_inverseMass;

		particle->addForce(val);
	}

	//----- ParticleSpring

	void ParticleSpring::updateForce(Particle* particle, Real duration)
	{
		math::Vector3r force;
		force = particle->m_position;
		force -= m_other->m_position;


		Real magnitude = force.length();
		magnitude = fabsf(magnitude - m_realLength);
		magnitude += m_springConstant;

		force.normalize();
		force *= -magnitude;
		particle->addForce(force);
	}

	//----- ParticleAnchoredSpring

	void ParticleAnchoredSpring::updateForce(Particle* particle, Real duration)
	{
		math::Vector3r force;
		force = particle->m_position;
		force -= m_anchor;


		Real magnitude = force.length();
		magnitude = (m_restLength - magnitude) * m_springConstant;

		force.normalize();
		force *= magnitude;
		particle->addForce(force);
	}

	//----- ParticleBungee

	void ParticleBungee::updateForce(Particle* particle, Real duration)
	{
		math::Vector3r force;
		force = particle->m_position;
		force -= m_other->m_position;


		Real magnitude = force.length();
		if (magnitude <= m_restLength) return;

		magnitude = m_springConstant * (m_restLength - magnitude);

		force.normalize();
		force *= -magnitude;
		particle->addForce(force);
	}

	//----- ParticleBouyancy

	void ParticleBouyancy::updateForce(Particle* particle, Real duration)
	{
		Real depth = particle->m_position.y;

		if (depth >= m_waterHeight + m_maxDepth) return;

		math::Vector3r force;

		if (depth <= m_waterHeight - m_maxDepth)
		{
			force.y = m_liquidDensirt * m_volume;
			particle->addForce(force);
			return;
		}

		force.y = m_liquidDensirt * m_volume * (depth - m_maxDepth - m_waterHeight) / 2 * m_maxDepth;
		particle->addForce(force);
	}

	//----- ParticleForceRegistry

	void ParticleForceRegistry::add(Particle* particle, ParticleForceGenerator * generator)
	{
		registration.push_back(ParticleForceRegistration(generator, particle));
	}

	void ParticleForceRegistry::clear()
	{
		registration.clear();
	}

	void ParticleForceRegistry::updateForces(Real duration)
	{
		std::vector<ParticleForceRegistration>::iterator iter;
		for (iter = registration.begin(); iter != registration.end(); iter++) {
			iter->m_fg->updateForce(iter->m_particle, duration);
		}
	}

	Particle* ParticleForceRegistry::getParticle(int index)
	{
		std::vector<ParticleForceRegistration>::iterator iter;
		int counter = 0;
		for (iter = registration.begin(); iter != registration.end(); iter++) {
			if (counter == index) {
				return iter->m_particle;
			}
			counter++;
		}
		return nullptr;
	}

	//----- GravityForce
	void GravityForce::updateForce(RigidBody *body, Real duration)
	{
		if (body->getInverseMass() == 0) return;

		math::Vector3r val = m_gravity * body->getInverseMass();

		body->addForce(val);
	}

	//----- npPendulumForce
	LinearPendulumForce::LinearPendulumForce(const math::Vector3r& startPos,
		const math::Vector3r& endPos,
		const Real& time)
	{
		if (endPos <= startPos) {
			m_startPos = endPos;
			m_endPos = startPos;
		}
		else {
			m_startPos = startPos;
			m_endPos = endPos;
		}
		m_pendulumForce = (endPos - startPos) * (1.0f / time);
		m_isReturning = endPos <= startPos;
		m_maxTime = time;
	}

	void LinearPendulumForce::updateForce(RigidBody *body, Real duration)
	{
		if (body->getInverseMass() == 0) return;

		if (body->getWorldPosition() >= m_endPos) {
			if (!m_isReturning) {
				math::Vector3r directonalVector = m_startPos - m_endPos;
				m_pendulumForce = directonalVector * (1.0f / m_maxTime);
				m_isReturning = true;
			}
		} else if (body->getWorldPosition() <= m_startPos) {
			if (m_isReturning) {
				math::Vector3r directonalVector = m_endPos - m_startPos;
				m_pendulumForce = directonalVector * (1.0f / m_maxTime);
				m_isReturning = false;
			}
		}
		math::Vector3r finalValue = m_pendulumForce * 0.1f;
		body->addForce(finalValue);
	}

	//----- ForceRegistry

	void ForceRegistry::add(RigidBody* rigidBody, ForceGenerator *generator)
	{
		registration.push_back(npForceRegistration(generator, rigidBody));
	}

	void ForceRegistry::clear()
	{
		registration.clear();
	}

	void ForceRegistry::updateForces(Real duration)
	{
		std::vector<npForceRegistration>::iterator iter;
		for (iter = registration.begin(); iter != registration.end(); iter++) {
			iter->m_fg->updateForce(iter->m_rigidBody, duration);
		}
	}

	RigidBody* ForceRegistry::getRigidBody(int index)
	{
		std::vector<npForceRegistration>::iterator iter;
		int counter = 0;
		for (iter = registration.begin(); iter != registration.end(); iter++) {
			if (counter == index) {
				return iter->m_rigidBody;
			}
			counter++;
		}
		return nullptr;
	}

}