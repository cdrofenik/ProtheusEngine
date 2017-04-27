#ifndef QUARTERNION_HPP
#define QUARTERNION_HPP

#include "Vector3.hpp"
#include <math.h>

class Quarternion
{
public:
	union {
		struct {
			Real r;
			Real i;
			Real j;
			Real k;
		};

		Real data[4];
	};

	Quarternion(const Real &_r = 0, const Real &_i = 0,
		const Real &_j = 0, const Real &_k = 0) :
		r(_r), i(_i), j(_j), k(_k) {}

	void normalize()
	{
		Real d = r*r + i*i + j*j + k*k;

		if (d == 0) {
			r = 1;
			return;
		}

		d = 1.0f / (Real)sqrt(d);
		r *= d;
		i *= d;
		j *= d;
		k *= d;
	}

	void operator*=(const Quarternion& _multiplier)
	{
		Quarternion result, q  = *this;
		result.r = q.r * _multiplier.r - q.i * _multiplier.i - q.j * _multiplier.j - q.k * _multiplier.k;
		result.i = q.r * _multiplier.i + q.i * _multiplier.r + q.j * _multiplier.k - q.k * _multiplier.j;
		result.j = q.r * _multiplier.j + q.j * _multiplier.r + q.k * _multiplier.i - q.i * _multiplier.k;
		result.k = q.r * _multiplier.k + q.k * _multiplier.r + q.i * _multiplier.j - q.j * _multiplier.i;
		
		*this = result;
	}

	Quarternion rotateByVector(const Vector3r& _vector)
	{
		Quarternion q(0, _vector.x, _vector.y, _vector.z);
		//(*this) *= q;
		Quarternion result;
		result *= q;
	}

	void addScaledVector(const Vector3r& _vector, const Real& _scale)
	{
		Quarternion q(0, _vector.x * _scale, _vector.y * _scale, _vector.z * _scale);
		q *= *this;
		r += q.r * (0.5f);
		i += q.i * (0.5f);
		j += q.j * (0.5f);
		k += q.k * (0.5f);
	}

};
#endif