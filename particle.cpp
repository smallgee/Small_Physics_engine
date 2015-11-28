#include <assert.h>
#include "include\smallPhyszc\particle.h"

using namespace smallphyzc;

void particle::intergrate(real duration)
{
	assert(duration >0.0);
    
	//update position 
	position.addScaledVector(velocity,duration);

	//calculate the accelarion from the force
	Vector3 resultingAccum = acceleration;
	resultingAccum.addScaledVector(forceAccum, inverseMass);

	//update velocity from the accelation
	velocity.addScaledVector(resultingAccum, duration);

	//imposing drag
	velocity *=real_pow(damping, duration);

}



