#ifndef PRECISION_HPP
#define PRECISION_HPP

namespace math {
	/*
	Defines a real number precision Prometheus Engine supports single- and double- precision versions.
	The default one is single-precision.
	*/
#if DOUBLE_PRECISION
	typedef double Real;
#define REAL_MAX DOUBLE_MAX
#else
	typedef float Real;
#define REAL_MAX _FMAX
#endif

#define DEF_PI 3.14159265
#define DEF_PI_2 1.57079632
#define DEF_NULL 0

#define TO_RADIAN(x) ((x) * DEF_PI / 180.0f)
#define TO_DEGREE(x) ((x) * 180.0f / DEF_PI)
}
#endif