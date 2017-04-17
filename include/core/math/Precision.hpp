#ifndef PRECISION_HPP
#define PRECISION_HPP

	/*
		Defines a real number precision Prometheus Engine supports single- and double- precision versions.
		The default one is single-precision.
		*/
#if DOUBLE_PRECISION
	typedef double Real;
	#define NP_REAL_MAX DOUBLE_MAX
#else
	typedef float Real;
	#define NP_REAL_MAX _FMAX
#endif

#define NP_PI 3.14159265
#define M_PI_2 1.57079632
#define NP_NULL 0

#define NP_NULL 0

#define ToRadian(x) ((x) * NP_PI / 180.0f)
#define ToDegree(x) ((x) * 180.0f / NP_PI)


#endif