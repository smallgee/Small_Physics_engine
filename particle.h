#include "include\smallPhyszc\spMath.h"


namespace smallphyzc
{
	class particle
	{
	public:
	  //position of the particle in the world space
	  Vector3 position;

	  //velocity of the particle in world space
	  Vector3 velocity;

	  //accelarion of the particle|this vector can be used to set the gravity or initial accelartion
	  Vector3 acceleratiom;

	  //amount of damping applied to linear motion|also removes numerical instabilities brought by inacuracies in the intergrator.
	  real damping;

	  //holds the inverse mass of the particle
	  real inverseMass;

	  //moves the particle in world space by a given amount
	  void intergrate(real duration);
    };
}