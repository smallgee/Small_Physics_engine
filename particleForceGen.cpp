#include <vector>
#include "particle.h"
#include "precision.h"
#include "spMaths.h"
#include "particleForceGen.h"


using namespace smallPhyzc;


void particleForceRegistry::updateForces(real duration)
{
	registry::iterator i = registrations.begin();
	for (; i != registrations.end(); i++)
	{
	i->fg->updateForce(i->particle, duration);
	}
}

void particleGravity::updateForces(particle *particle, real duration)
{
   //check if particle has infinite mass
	if(!particle->hasInfiniteMass())return;

	// Apply the mass-scaled force to the particle.
    particle->addForce(gravity * particle->getMass())

}

void particleDrag::updateForces(particle* particle, real duration)
	{
	Vector3 force;
	particle->getVelocity(&force);
	// Calculate the total drag coefficient.
	real dragCoeff = force.magnitude();
	dragCoeff = k1 * dragCoeff + k2 * dragCoeff * dragCoeff;
	// Calculate the final force and apply it.
	force.normalize();
	force *= -dragCoeff;
	particle->addForce(force);
}

void ParticleSpring::updateForce(Particle* particle, real duration)
{
	// Calculate the vector of the spring.
	Vector3 force;
	6.2 Springlike Force Generators 85
	particle->getPosition(&force);
	force -= other->getPosition();
	// Calculate the magnitude of the force.
	real magnitude = force.magnitude();
	magnitude = real_abs(magnitude - restLength);
	magnitude *= springConstant;
	// Calculate the final force and apply it.
	force.normalize();
	force *= -magnitude;
	particle->addForce(force);
};

void ParticleAnchoredSpring::updateForce(particle* particle,
real duration)
{
	// Calculate the vector of the spring.
	Vector3 force;
	particle->getPosition(&force);
	force -= *anchor;
	// Calculate the magnitude of the force.
	real magnitude = force.magnitude();
	magnitude = real_abs(magnitude - restLength);
	magnitude *= springConstant;
	// Calculate the final force and apply it.
	force.normalize();
	force *= -magnitude;
	particle->addForce(force);
};

void ParticleBungee::updateForce(Particle* particle, real duration)
{
	// Calculate the vector of the spring.
	Vector3 force;
	particle->getPosition(&force);
	force -= other->getPosition();
	// Check if the bungee is compressed.
	real magnitude = force.magnitude();
	if (magnitude <= restLength) return;
	// Calculate the magnitude of the force.
	magnitude = springConstant * (restLength - magnitude);
	// Calculate the final force and apply it.
	force.normalize();
	force *= -magnitude;
	particle->addForce(force);
}

void ParticleBuoyancy::updateForce(particle* particle, real duration)
{
	// Calculate the submersion depth.
	real depth = particle->getPosition().y;
	// Check if we�re out of the water.
	if (depth >= waterHeight + maxDepth) return;
	Vector3 force(0,0,0);
	// Check if we�re at maximum depth.
	if (depth <= waterHeight - maxDepth)
	{
	force.y = liquidDensity * volume;
	particle->addForce(force);
	return;
	}
	// Otherwise we are partly submerged.
	force.y = liquidDensity * volume *
	(depth - maxDepth - waterHeight) / 2 * maxDepth;
	particle->addForce(force);
}

void ParticleFakeSpring::updateForce(particle* particle, real duration)
{
	// Check that we do not have infinite mass.
	if (!particle->hasFiniteMass()) return;
	// Calculate the relative position of the particle to the anchor.
	Vector3 position;
	particle->getPosition(&position);
	position -= *anchor;
	// Calculate the constants and check whether they are in bounds.
	real gamma = 0.5f * real_sqrt(4 * springConstant - damping*damping);
	if (gamma == 0.0f) return;
	Vector3 c = position * (damping / (2.0f * gamma)) +
	particle->getVelocity() * (1.0f / gamma);
	// Calculate the target position.
	Vector3 target = position * real_cos(gamma * duration) +
	c * real_sin(gamma * duration);
	target *= real_exp(-0.5f * duration * damping);
	6.3 Stiff Springs 99
	// Calculate the resulting acceleration and therefore the force
	Vector3 accel = (target - position) * (1.0f / duration*duration) -particle->getVelocity() * duration;
	particle->addForce(accel * particle->getMass());
}