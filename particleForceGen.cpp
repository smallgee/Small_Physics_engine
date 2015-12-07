#include <vector>
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