#ifndef FORCEGENERATOR_H
#define FORCEGENERATOR_H

#include "physics\dynamics\Particle.h"
#include "physics\dynamics\RigidBody.h"

#include <vector>

namespace physics {

	class ParticleForceGenerator
	{
	public:
		virtual void updateForce(Particle* particle, math::Real duration) = 0;
	};

	class ParticleGravity : public ParticleForceGenerator
	{
	public:
		ParticleGravity(math::Vector3r gravity) : m_gravity(gravity) {};
		~ParticleGravity() {};
		
		virtual void updateForce(Particle* particle, math::Real duration);

	private:
		math::Vector3r m_gravity;
	};

	class ParticleSpring : public ParticleForceGenerator
	{
	public:
		ParticleSpring(Particle* particle, math::Real springContant, math::Real length) :
			m_other(particle), m_springConstant(springContant), m_realLength(length) {};
		~ParticleSpring() {};


		virtual void updateForce(Particle* particle, math::Real duration);

	private:
		Particle* m_other;
		math::Real m_springConstant;
		math::Real m_realLength;
	};

	class ParticleAnchoredSpring : public ParticleForceGenerator
	{
	public:
		ParticleAnchoredSpring(math::Vector3r anchor, math::Real springContant, math::Real length) :
			m_anchor(anchor), m_springConstant(springContant), m_restLength(length) {};
		~ParticleAnchoredSpring() {};

		virtual void updateForce(Particle* particle, math::Real duration);

	private:
		math::Vector3r m_anchor;
		math::Real m_springConstant;
		math::Real m_restLength;
	};

	class ParticleBungee : public ParticleForceGenerator
	{
	public:
		ParticleBungee(Particle* particle, math::Real springContant, math::Real length) :
			m_other(particle), m_springConstant(springContant), m_restLength(length) {};
		~ParticleBungee() {};

		virtual void updateForce(Particle* particle, math::Real duration);

	private:
		Particle* m_other;
		math::Real m_springConstant;
		math::Real m_restLength;
	};

	class ParticleBouyancy : public ParticleForceGenerator
	{
	public:
		ParticleBouyancy(math::Real maxDepth, math::Real volume, math::Real waterHeight,
			math::Real liquidDensity = 1000.0f) :
			m_maxDepth(maxDepth), m_volume(volume), m_waterHeight(waterHeight),
			m_liquidDensirt(liquidDensity) {};
		~ParticleBouyancy() {};

		virtual void updateForce(Particle* particle, math::Real duration);

	private:
		math::Real m_maxDepth;
		math::Real m_volume;
		math::Real m_waterHeight;
		math::Real m_liquidDensirt;
	};

	class ParticleForceRegistry
	{
	protected:
		struct ParticleForceRegistration
		{
			ParticleForceRegistration(ParticleForceGenerator *fg, Particle *particle) :
				m_particle(particle), m_fg(fg) {};

			Particle *m_particle;
			ParticleForceGenerator *m_fg;
		};

		typedef std::vector<ParticleForceRegistration> _Registry;
		_Registry registration;

	public:

		void add(Particle* particle, ParticleForceGenerator * generator);

		Particle* getParticle(int index);

		void remove(Particle* particle, ParticleForceGenerator * generator);

		void clear();

		void updateForces(math::Real duration);
	};

	class ForceGenerator
	{
	public:
		virtual void updateForce(RigidBody *body, math::Real duration) = 0;
	};

	class GravityForce : public ForceGenerator
	{
		math::Vector3r m_gravity;
	public:
		GravityForce(const math::Vector3r& gravity) : m_gravity(gravity) {};
		~GravityForce() {};
		virtual void updateForce(RigidBody *body, math::Real duration);
	};

	class LinearPendulumForce : public ForceGenerator
	{
	public:
		LinearPendulumForce(const math::Vector3r& startPos,
			const math::Vector3r& endPos,
			const math::Real& time);
		~LinearPendulumForce() {};
		virtual void updateForce(RigidBody *body, math::Real duration);
	private:
		math::Vector3r m_startPos;
		math::Vector3r m_endPos;
		math::Vector3r m_pendulumForce;
		math::Real m_maxTime;
		bool m_isReturning;
	};

	struct IndexForces
	{
		unsigned int index;
		ForceGenerator* force;
	};

	class ForceRegistry
	{
	protected:
		struct npForceRegistration
		{
			npForceRegistration(ForceGenerator *fg, RigidBody *rigidBody) :
				m_rigidBody(rigidBody), m_fg(fg) {};

			RigidBody *m_rigidBody;
			ForceGenerator *m_fg;
		};

		typedef std::vector<npForceRegistration> _Registry;
		_Registry registration;

	public:
		void add(RigidBody* rigidBody, ForceGenerator *generator);

		RigidBody* getRigidBody(int index);

		void remove(RigidBody* rigidBody, ForceGenerator * enerator);

		void clear();

		void updateForces(math::Real duration);
	};
}

#endif