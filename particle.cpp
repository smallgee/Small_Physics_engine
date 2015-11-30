#include <assert.h>
#include "particle.h"
#include "precision.h"

using namespace smallphyzc;

void particle::intergrate(real duration)
{
assert(duration > 0.0);
// Update linear position.
position.addScaledVector(velocity, duration);
// Work out the acceleration from the force.
Vector3 resultingAcc = acceleration;
resultingAcc.addScaledVector(forceAccum, inverseMass);

// Update linear velocity from the acceleration.
velocity.addScaledVector(resultingAcc, duration);
// Impose drag.
velocity *= real_pow(damping, duration);
// Clear the forces.
clearAccum();
}

void particle::clearAccum()
{
   forceAccum.clear();
}

void particle::addForce(Vector3 &force)
{
	forceAccum +=force;
}


