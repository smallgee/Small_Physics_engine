

//define the precision of the square root operator
#define real_sqrt sqrtf
//define the precision of the power operator
#define real_pow powf
namespace smallphyzc
{
	/* the reason for defining the [float real] here is if you ever choose to compile for
	double precision floating point(say for a 64bit machine)all you have to do is change the type real here and it
	will propergate everywhere it has been used in the math libraries(in this case the spMath.h and spMath.cpp)
	*/
	typedef float real;

}