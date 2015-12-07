#include "spMaths.h"


namespace smallPhyzc
{
	class particle
	{
	public:
	  //position of the particle in the world space
	  Vector3 position;

	  //velocity of the particle in world space
	  Vector3 velocity;

	  //accelarion of the particle|this vector can be used to set the gravity or initial accelartion
	  Vector3 acceleration;

	  //holds the accumulated force
	  Vector3 forceAccum;

	  //amount of damping applied to linear motion|also removes numerical instabilities brought by inacuracies in the intergrator.
	  real damping;

	  //holds the inverse mass of the particle
	  real inverseMass;

	  //moves the particle in world space by a given amount
	  void intergrate(real duration);

	  //clears forceAcctmm automatically after the intergrator runs
	  void clearAccum();

	  //method for adding force into the accumulator
	  void addForce(Vector3 &force);
    };
}