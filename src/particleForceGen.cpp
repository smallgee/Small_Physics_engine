#include <vector>

using namespace smallphyzc:


void ParticleForceRegistry::updateForces(real duration)
{
	Registry::iterator i = registrations.begin();
	for (; i != registrations.end(); i++)
	{
	i->fg->updateForce(i->particle, duration);
	}
}

void particleGravity::updateForce(Particle *particle, real duration)
{
   //check if particle has infinite mass
	if(!particle->hasInfiniteMass())return;

	// Apply the mass-scaled force to the particle.
    particle->addForce(gravity * particle->getMass())

}

void ParticleDrag::updateForce(Particle* particle, real duration)
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