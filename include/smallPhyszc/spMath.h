a#include "precision.h"


namespace smallphyzc
{
	class Vector3
	{
	public:
	
		//holds the values for the x,y and z cordinates
		real x,y,z;

	private:

		//holds the padding value for correct bit allighnment
		real pad;

	public:
		//default constructor|creates a zero vector
		Vector3():x(0),y(0),z(0){}

		//explicit contructor |with a user defined values
		Vector3(const real x,const real y, const real z):x(x),y(y),z(z){}

		//inverts the values of the vector
		void invert(){x=-x;y=-y,z=-z;}

		//get the magintude of a vector
		real magnitude() const {return real_sqrt(x*x+y*y+z*z);}

		//get the magnitude of a vector
		real squareMagnitude() const {return x*x+y*y+z*z;}

		//turns a non-zero vector into a unit vector
		void normalize()
		{
		real l = magnitude();
			if (l > 0)
			{
			(*this)*=((real)1)/l;
			}
		}

		//multiplies this vector by a given scalar
		void operator *=(const real value)
		{
		  x *=value;
		  y *=value;
		  z*=value;
		}

		//return a vector scale to a given value
		Vector3 operator*(const real value)
		{
		
			return Vector3(x*value,y*value,z*value);
		}

		//adds a given vector to this
		void operator+=(Vector3 &v)
		{
		
			x += v.x;
			y += v.y;
			z += v.z;
		}

		//returns a given vector added to this
		Vector3 operator+(Vector3 &v)const
		{
		  return Vector3(x+v.x,y+v.y,z+v.z);
		}

		//subtracts a given vector from this
		void operator-=(Vector3 &v)
		{
		  x -=v.x;
		  y -=v.y;
		  z -=v.z;
		}

		//returns the value of a given vector subtracted from this
		Vector3 operator-(Vector3 &v)const
		{
		  return Vector3(x-v.x,y-v.y,z-v.z);
		}

		//add a given vector[Vector3 vector] to this | scaled by the given a mount [real scale]
		void addScaledVector(const Vector3& vector, real scale)
		{
		x += vector.x * scale;
		y += vector.y * scale;
		z += vector.z * scale;
		}

        //calculate the component-wise product of this vector with the given vector
		Vector3 componentProduct(const Vector3 &v)const
		{
			return Vector3(x*v.x,y*v.y,z*v.z);
		}

		//calculate the component-wise product of this vector and set it to its results
		void componentProductUpdate(const Vector3 &v)
		{
			x*v.x;
			y*=v.y;
			z*=v.z;
		}

		//calculate and return the scalar product of this vector with the given vector
		real scalarProduct(const Vector3 &v)const
		{
			return x*v.x+y*v.y+z*v.z;
		}

		//calculates and returns a vector product of this vector with a given vector
		Vector3 vectorProduct(const Vector3 &v) const
		{
			return Vector3
			(y*v.z-z*v.y,
			z*v.x-x*v.z,
			x*v.y-y*v.x);
		}


	    //Updates this vector to be the vector product of its current
		//value and the given vector.
		void operator %=(const Vector3 &v)
		{
			*this = vectorProduct(v);
		}

		//Calculates and returns the vector product of this vector
		//with the given vector.
		
		Vector3 operator%(const Vector3 &v) const
		{
		return Vector3(y*v.z-z*v.y,
		z*v.x-x*v.z,
		x*v.y-y*v.x);
		}
	};


}