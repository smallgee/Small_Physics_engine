#include "particle.h"
#include "precision.h"

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
		void updateForces(real duration)
	};



}

