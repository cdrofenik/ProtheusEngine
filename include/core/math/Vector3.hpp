#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include "Precision.hpp"

//system directory
#include <math.h>

namespace math {

	template<typename T>
	class Vector3 {

	public:
		union
		{
			struct {
				T x;
				T y;
				T z;
			};
			
			T data[3];
		};
		
		Vector3() : x(0), y(0), z(0) {}
		Vector3(const T& xx, const T& yy, const T& zz) : x(xx), y(yy), z(zz) {}

		/*!
		Returns square length value without the sqrt
		*/
		T squareLength() const
		{
			return (x * x) + (y * y) + (z * z);
		}

		/*!
		Returns the length of this vector.
		*/
		T length() const
		{
			return (Real)sqrt((x * x) + (y * y) + (z * z));
		}

		/*!
		Inverts the vector values.
		*/
		void invert()
		{
			x = -x;
			y = -y;
			z = -z;
		}

		/*!
		Normalizes the vector = vector / length
		*/
		Vector3<T>& normalize()
		{
			const Real l = (Real)sqrt(x * x + y * y + z * z);

			x /= l;
			y /= l;
			z /= l;

			return *this;
		}

		/*!
		\param vector a referenced Vector3.
		\param scale a scale with a real value.
		*/
		void addScaledVector(const Vector3<T>& v, const T& scale)
		{
			x += v.x * scale;
			y += v.y * scale;
			z += v.z * scale;
		}

		bool isNear(const Vector3<T>& v) const
		{
			return fabs(x - v.x) < 0.01f && fabs(y - v.y) < 0.01f && fabs(z - v.z) < 0.01f;
		}

		/*!
		\param vector a referenced Vector3.
		*/
		void componentProductUpdate(const Vector3<T>& v)
		{
			x *= v.x;
			y *= v.y;
			z *= v.z;
		}

		/*!
		Angle between two vectors in degrees
		*/
		T angle(const Vector3<T>& v)
		{
			auto top = (x * v.x) + (y * v.y) + (z * v.z);
			auto bottom = this->length() * v.length();
			return (T)(acos(top / bottom) * (180 / DEF_PI));
		}

		void operator+=(const Vector3<T>& v) {
			x += v.x;
			y += v.y;
			z += v.z;
		}

		void operator-=(const Vector3<T>& v) {
			x -= v.x;
			y -= v.y;
			z -= v.z;
		}

		void operator*=(const T& v) {
			x *= v;
			y *= v;
			z *= v;
		}

		bool operator!=(const Vector3<T>& v) {
			return x != v.x || y != v.y || z != v.z;
		}

		void operator%=(const Vector3<T>& v) {
			Vector3<T> r(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
			(*this) = r;
		}

		Vector3<T> operator+(const Vector3<T>& v) const {
			return Vector3(x + v.x, y + v.y, z + v.z);
		}

		Vector3<T> operator-(const Vector3<T>& v) const {
			return Vector3(x - v.x, y - v.y, z - v.z);
		}

		Vector3<T> operator*(const T& v) const {
			return Vector3(x * v, y * v, z * v);
		}

		Real operator*(const Vector3<T>& v) const {
			return (x * v.x) + (y * v.y) + (z * v.z);
		}

		/*!
		Returns cross product between two vectors
		*/
		Vector3<T> operator%(const Vector3<T>& v) const {
			return Vector3<T>(
				y*v.z - z*v.y,
				z*v.x - x*v.z,
				x*v.y - y*v.x);
		}

		bool operator>=(const Vector3<T>& v) const {
			return x >= v.x && y >= v.y && z >= v.z;
		}

		bool operator<=(const Vector3<T>& v) const {
			return x <= v.x && y <= v.y && z <= v.z;
		}
	};

	typedef Vector3<Real> Vector3r;
	typedef Vector3<int> Vector3i;
	typedef Vector3<unsigned int> Vector3ui;
}
#endif