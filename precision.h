

//define the precision of the square root operator
#define real_sqrt sqrtf
//define the precision of the power operator
#define real_pow powf
//defining an absolute magnitude value
#define real_abs fabsf
/** Defines the precision of the sine operator. */
#define real_sin sinf
/** Defines the precision of the cosine operator. */
#define real_cos cosf
/** Defines the precision of the exponent operator. */
#define real_exp expf

namespace smallPhyzc
{
	/* the reason for defining the [float real] here is if you ever choose to compile for
	double precision floating point(say for a 64bit machine)all you have to do is change the type real here and it
	will propergate everywhere it has been used in the math libraries(in this case the spMath.h and spMath.cpp)
	*/
	typedef float real;

}