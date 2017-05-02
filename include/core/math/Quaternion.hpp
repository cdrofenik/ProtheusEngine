#ifndef QUARTERNION_HPP
#define QUARTERNION_HPP

#include "Vector3.hpp"

//system directory
#include <math.h>

namespace math {

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

		Quarternion(const Real& rr = 0, const Real& ii = 0,
			const Real& jj = 0, const Real& kk = 0) :
			r(rr), i(ii), j(jj), k(kk) {}

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

		void operator*=(const Quarternion& multiplier)
		{
			Quarternion result, q = *this;
			result.r = q.r * multiplier.r - q.i * multiplier.i - q.j * multiplier.j - q.k * multiplier.k;
			result.i = q.r * multiplier.i + q.i * multiplier.r + q.j * multiplier.k - q.k * multiplier.j;
			result.j = q.r * multiplier.j + q.j * multiplier.r + q.k * multiplier.i - q.i * multiplier.k;
			result.k = q.r * multiplier.k + q.k * multiplier.r + q.i * multiplier.j - q.j * multiplier.i;

			*this = result;
		}

		Quarternion rotateByVector(const Vector3r& vector)
		{
			Quarternion q(0, vector.x, vector.y, vector.z);
			//(*this) *= q;
			Quarternion result;
			result *= q;
		}

		void addScaledVector(const Vector3r& vector, const Real& scale)
		{
			Quarternion q(0, vector.x * scale, vector.y * scale, vector.z * scale);
			q *= *this;
			r += q.r * (0.5f);
			i += q.i * (0.5f);
			j += q.j * (0.5f);
			k += q.k * (0.5f);
		}

	};
}
#endif