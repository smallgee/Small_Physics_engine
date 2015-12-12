#include "particle.h"
#include "precision.h"
#include "spMaths.h"

//force generator for adding force to particls
class particleForceGenerator
{

public :
//overload this 
virtual void updateForce(particle *particle, real duration) = 0;


}

#include <vector>

namespace smallPhyzc
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
		\/**
	* A force generator that applies a spring force.
	*/
	class ParticleSpring : public particleForceGenerator
	{
		/** The particle at the other end of the spring. */
		particle *other;
		/** Holds the spring constant. */
		real springConstant;
		/** Holds the rest length of the spring. */
		real restLength;
		public:
		/** Creates a new spring with the given parameters. */
		ParticleSpring(Particle *other,
		real springConstant, real restLength);
		/** Applies the spring force to the given particle. */
		virtual void updateForce(Particle *particle, real duration);
	};

		/**
	* A force generator that applies a spring force, where
	* one end is attached to a fixed point in space.
	*/
	class ParticleAnchoredSpring : public particleForceGenerator
	{
		/** The location of the anchored end of the spring. */
		Vector3 *anchor;
		/** Holds the spring constant. */
		real springConstant;
		/** Holds the rest length of the spring. */
		6.2 Springlike Force Generators 87
		real restLength;
		public:
		/** Creates a new spring with the given parameters. */
		ParticleAnchoredSpring(Vector3 *anchor,
		real springConstant, real restLength);
		/** Applies the spring force to the given particle. */
		virtual void updateForce(particle *particle, real duration);
		};

	/**
* A force generator that applies a spring force only
* when extended.
*/
class ParticleBungee : public particleForceGenerator
	{
	/** The particle at the other end of the spring. */
	particle *other;
	/** Holds the spring constant. */
	real springConstant;
	/**
	* Holds the length of the bungee at the point it begins to
	* generate a force.
	*/
	real restLength;
	public:
	/** Creates a new bungee with the given parameters. */
	ParticleBungee(particle *other,
	real springConstant, real restLength);
	/** Applies the spring force to the given particle. */
	virtual void updateForce(particle *particle, real duration);
};

/**
* A force generator that applies a buoyancy force for a plane of
* liquid parallel to XZ plane.
*/
class ParticleBuoyancy : public ParticleForceGenerator
{
	/**
	* The maximum submersion depth of the object before
	* it generates its maximum buoyancy force.
	*/
	real maxDepth;
	/**
	* The volume of the object.
	*/
	real volume;
	/**
	* The height of the water plane above y=0. The plane will be
	* parallel to the XZ plane.
	*/
	real waterHeight;
	/**
	* The density of the liquid. Pure water has a density of
	* 1000 kg per cubic meter.
	*/
	real liquidDensity;
	public:
	/** Creates a new buoyancy force with the given parameters. */
	ParticleBuoyancy(real maxDepth, real volume, real waterHeight,
	real liquidDensity = 1000.0f);
	/** Applies the buoyancy force to the given particle. */
	virtual void updateForce(particle *particle, real duration);
};

/**
* A force generator that fakes a stiff spring force, and where
* one end is attached to a fixed point in space.
98 Chapter 6Springs and Springlike Things
*/
class ParticleFakeSpring : public particleForceGenerator
{
	/** The location of the anchored end of the spring. */
	Vector3 *anchor;
	/** Holds the spring constant. */
	real springConstant;
	/** Holds the damping on the oscillation of the spring. */
	real damping;
	public:
	/** Creates a new spring with the given parameters. */
	ParticleFakeSpring(Vector3 *anchor, real springConstant,
	real damping);
	/** Applies the spring force to the given particle. */
	virtual void updateForce(Particle *particle, real duration);
};

