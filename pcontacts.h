//a contacts represent contacts between two object.
//resolving a contacts applies impulse to them, removing their interprenetrability
#include "precision.h"
#include "particle.h"
#include "spMaths.h"

class ParticleContact
{

public:
	//holds the particle that is involved in the contact
	particle* particle[2];

	//hold the coeficient of restitution of the particle
	real restitution;

	//holds the direction of the contact|a normal vector

	Vector3 contactNormal;
protected:
	//resolve this contact for both velocity and interpenetrability
	void resolve(real duration);

	//calculate the separanting velocity at this contact

	real separatingVelocity()const;
private:
	//handles the impulses
	void resolveVelocity(real duration);


}