#ifndef PARTICLE_H
#define PARTICLE_H

#include "core/math/Vector3.hpp"

namespace physics {

	class Particle
	{
	public:
		Particle(math::Vector3r pos, math::Vector3r velocity,
			math::Vector3r acc, math::Real damp, math::Real inMass) :
			m_position(pos),
			m_velocity(velocity),
			m_acceleration(acc),
			m_dampening(damp),
			m_inverseMass(inMass) {};
		
		~Particle() {};

		void integrate(math::Real duration);

		void addForce(const math::Vector3r& force);
		void clearAccum();

	//private:
		math::Vector3r m_position;
		math::Vector3r m_velocity;
		math::Vector3r m_acceleration;

		math::Real m_dampening;
		math::Real m_inverseMass;

		math::Vector3r m_forceAccum;
	};
}

#endif