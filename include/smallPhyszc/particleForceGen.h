#include "particle.h"
#include "precision.h"
#include "spMath.h"

//force generator for adding force to particls
class particleForceGenerator
{

public :
//overload this 
virtual void updateForce(particle *particle, real duration) = 0;


}

#include <vector>

namespace smallphyzc
{	
	//holds the force gen and the particles they apply to
	class particleForceRegistry
	{
	protected:
		//keeps tracl of one force gen and the particle it applies to
		struct particleForceRegistration
		{
			particle *particle;
			particleForceGenerator *fg;
		};
	    //holds list of registraionsl
		typedef std::vector<particleForceRegistration> registry;
		registry registrations;
	public:
		//register a given force to a given particle
		void add(particle *particle, particleForceGenerator *fg);

		//removes a given the given registation pair from the registry
		void remove(particle *particle, particleForceGenerator *fg);

		//clear registry|does not delete the forces or the particles, just their connections
		void clear();

		//calls all force generators to update the forces of their particle;
		void updateForces(real duration);
	};

	class particleGravity : public particleForceGenerator
	{
	  //force gen that applies gravitational force to a particle
	  //multiple particles can use one instance of this force gen.
	
		Vector3 gravity;

	public:

		//create the gen with the given velocity
		particleGravity(const Vector3 &gravity);

		//apply the gravity to the given particle
		virtual void updateForces(particle *particle, real duration);
		
	};

	//force gen for applying drag to a particle
	//a single instance of this force gen can be used by multiple particles
	class particleDrag : particleForceGenerator
	{
	
		//holds the velocity drag co-efficients
		real k1;
		real k2;
	public:
		//creates the drag with the folling co-efficients
		particleDrag(real k1,real k2);

		//apply the drags to the given paricles
		virtual void updateForces(particle *particle , real duration);

	};


}

