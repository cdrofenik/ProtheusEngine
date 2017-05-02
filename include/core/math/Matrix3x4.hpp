#ifndef MATRIX3X4_HPP
#define MATRIX3X4_HPP

#include "Vector3.hpp"
#include "Quaternion.hpp"

namespace math {

	class Matrix3x4
	{
	public:
		Real m[12]; //TODO dodaj komentarje za vse operacije

		Matrix3x4(const Real& v = 1.0f)
		{
			m[0] = m[5] = m[10] = v; // diagonal elements
			m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = 0.0f;
		}

		Matrix3x4(const Real& a0, const Real& a1, const Real& a2, const Real& a3,
			const Real& a4, const Real& a5, const Real& a6, const Real& a7,
			const Real& a8, const Real& a9, const Real& a10, const Real& a11)
		{
			m[0] = a0; m[1] = a1; m[2] = a2; m[3] = a3;
			m[4] = a4; m[5] = a5; m[6] = a6; m[7] = a7;
			m[8] = a8; m[9] = a9; m[10] = a10; m[11] = a11;
		}

		Vector3r operator*(const Vector3r& vector) const
		{
			return Vector3r(
				vector.x * m[0] + vector.y * m[1] + vector.z * m[2] + m[3],
				vector.x * m[4] + vector.y * m[5] + vector.z * m[6] + m[7],
				vector.x * m[8] + vector.y * m[9] + vector.z * m[10] + m[11]
			);
		}

		Matrix3x4 operator*(const Matrix3x4& rmat) const
		{
			return Matrix3x4(
				m[0] * rmat.m[0] + m[1] * rmat.m[4] + m[2] * rmat.m[8],
				m[0] * rmat.m[1] + m[1] * rmat.m[5] + m[2] * rmat.m[9],
				m[0] * rmat.m[2] + m[1] * rmat.m[6] + m[2] * rmat.m[10],
				m[0] * rmat.m[3] + m[1] * rmat.m[7] + m[2] * rmat.m[11] + m[3],

				m[4] * rmat.m[0] + m[5] * rmat.m[4] + m[6] * rmat.m[8],
				m[4] * rmat.m[1] + m[5] * rmat.m[5] + m[6] * rmat.m[9],
				m[4] * rmat.m[2] + m[5] * rmat.m[6] + m[6] * rmat.m[10],
				m[4] * rmat.m[3] + m[5] * rmat.m[7] + m[6] * rmat.m[11] + m[7],

				m[8] * rmat.m[0] + m[9] * rmat.m[4] + m[10] * rmat.m[8],
				m[8] * rmat.m[1] + m[9] * rmat.m[5] + m[10] * rmat.m[9],
				m[8] * rmat.m[2] + m[9] * rmat.m[6] + m[10] * rmat.m[10],
				m[8] * rmat.m[3] + m[9] * rmat.m[7] + m[10] * rmat.m[11] + m[11]
			);
		}

		void operator*=(const Matrix3x4& rmat)
		{
			Real v1, v2, v3, v4;
			v1 = m[0] * rmat.m[0] + m[1] * rmat.m[4] + m[2] * rmat.m[8];
			v2 = m[0] * rmat.m[1] + m[1] * rmat.m[5] + m[2] * rmat.m[9];
			v3 = m[0] * rmat.m[2] + m[1] * rmat.m[6] + m[2] * rmat.m[10];
			v4 = m[0] * rmat.m[3] + m[1] * rmat.m[7] + m[2] * rmat.m[11] + m[3];
			m[0] = v1;
			m[1] = v2;
			m[2] = v3;
			m[3] = v4;

			v1 = m[4] * rmat.m[0] + m[5] * rmat.m[4] + m[6] * rmat.m[8];
			v2 = m[4] * rmat.m[1] + m[5] * rmat.m[5] + m[6] * rmat.m[9];
			v3 = m[4] * rmat.m[2] + m[5] * rmat.m[6] + m[6] * rmat.m[10];
			v4 = m[4] * rmat.m[3] + m[5] * rmat.m[7] + m[6] * rmat.m[11] + m[7];
			m[4] = v1;
			m[5] = v2;
			m[6] = v3;
			m[7] = v4;

			v1 = m[8] * rmat.m[0] + m[9] * rmat.m[4] + m[10] * rmat.m[8];
			v2 = m[8] * rmat.m[1] + m[9] * rmat.m[5] + m[10] * rmat.m[9];
			v3 = m[8] * rmat.m[2] + m[9] * rmat.m[6] + m[10] * rmat.m[10];
			v4 = m[8] * rmat.m[3] + m[9] * rmat.m[7] + m[10] * rmat.m[11] + m[11];
			m[8] = v1;
			m[9] = v2;
			m[10] = v3;
			m[11] = v4;
		}

		Vector3r transform(const Vector3r& vector) const
		{
			return (*this) * vector;
		}

		Real getDeterminant() const
		{
			return getDeterminant(*this);
		}

		Matrix3x4 inverse() const
		{
			Matrix3x4 result;
			result.setInverse(*this);
			return result;
		}

		void invert()
		{
			Matrix3x4 result;
			result.setInverse(*this);
			*this = result;
		}

		void setOrientation(const Quarternion& q, const Vector3r& pos)
		{
			m[0] = 1 - (2 * q.j * q.j + 2 * q.k * q.k);
			m[1] = 2 * q.i * q.j + 2 * q.k * q.r;
			m[2] = 2 * q.i * q.k - 2 * q.j * q.r;
			m[3] = pos.x;

			m[4] = 2 * q.i * q.j - 2 * q.k * q.r;
			m[5] = 1 - (2 * q.i * q.i + 2 * q.k * q.k);
			m[6] = 2 * q.j * q.k + 2 * q.i * q.r;
			m[7] = pos.y;

			m[8] = 2 * q.i * q.k + 2 * q.j * q.r;
			m[9] = 2 * q.j * q.k - 2 * q.i * q.r;
			m[10] = 1 - (2 * q.i * q.i + 2 * q.j * q.j);
			m[11] = pos.z;
		}

		Vector3r transformInverse(const Vector3r& vector) const
		{
			Vector3r tmp = vector;
			tmp.x -= m[3];
			tmp.y -= m[7];
			tmp.z -= m[11];
			return Vector3r(
				tmp.x * m[0] + tmp.y * m[4] + tmp.z * m[8],
				tmp.x * m[1] + tmp.y * m[5] + tmp.z * m[9],
				tmp.x * m[2] + tmp.y * m[6] + tmp.z * m[10]
			);
		}

		Vector3r getAxisValues(const unsigned int& axis) const
		{
			return Vector3r(m[axis], m[axis + 4], m[axis + 8]);
		}

	private:
		Real getDeterminant(const Matrix3x4& rmat) const
		{
			Real v1 = rmat.m[0] * rmat.m[5] * rmat.m[10];
			Real v2 = rmat.m[8] * rmat.m[1] * rmat.m[6];
			Real v3 = rmat.m[4] * rmat.m[9] * rmat.m[2];

			Real v4 = rmat.m[8] * rmat.m[5] * rmat.m[2];
			Real v5 = rmat.m[0] * rmat.m[9] * rmat.m[6];
			Real v6 = rmat.m[4] * rmat.m[1] * rmat.m[10];

			return v1 + v2 + v3 - v4 - v5 - v6;
		}

		void setInverse(const Matrix3x4& rmat)
		{
			Real det = getDeterminant(rmat);

			if (det == 0.0f) return;
			Real invDet = 1.0f / det;

			m[0] = (-rmat.m[9] * rmat.m[6] + rmat.m[5] * rmat.m[10]) * invDet;
			m[1] = (rmat.m[9] * rmat.m[2] - rmat.m[1] * rmat.m[10]) * invDet;
			m[2] = (-rmat.m[5] * rmat.m[2] + rmat.m[1] * rmat.m[6]) * invDet;

			m[3] = (rmat.m[9] * rmat.m[6] * rmat.m[3]
				- rmat.m[5] * rmat.m[10] * rmat.m[3]
				- rmat.m[9] * rmat.m[2] * rmat.m[7]
				+ rmat.m[1] * rmat.m[10] * rmat.m[7]
				+ rmat.m[5] * rmat.m[2] * rmat.m[11]
				- rmat.m[1] * rmat.m[6] * rmat.m[11]) * invDet;

			m[4] = (rmat.m[8] * rmat.m[6] - rmat.m[4] * rmat.m[10]) * invDet;
			m[5] = (-rmat.m[8] * rmat.m[2] + rmat.m[0] * rmat.m[10]) * invDet;
			m[6] = (rmat.m[4] * rmat.m[2] - rmat.m[0] * rmat.m[6]) * invDet;

			m[7] = (rmat.m[8] * rmat.m[6] * rmat.m[3]
				- rmat.m[4] * rmat.m[10] * rmat.m[3]
				- rmat.m[8] * rmat.m[2] * rmat.m[7]
				+ rmat.m[0] * rmat.m[10] * rmat.m[7]
				+ rmat.m[4] * rmat.m[2] * rmat.m[11]
				- rmat.m[0] * rmat.m[6] * rmat.m[11]) * invDet;

			m[8] = (-rmat.m[8] * rmat.m[5] + rmat.m[4] * rmat.m[9]) * invDet;
			m[9] = (rmat.m[8] * rmat.m[1] - rmat.m[0] * rmat.m[9]) * invDet;
			m[10] = (-rmat.m[4] * rmat.m[1] + rmat.m[0] * rmat.m[5]) * invDet;

			m[11] = (rmat.m[8] * rmat.m[5] * rmat.m[3]
				- rmat.m[4] * rmat.m[9] * rmat.m[3]
				- rmat.m[8] * rmat.m[1] * rmat.m[7]
				+ rmat.m[0] * rmat.m[9] * rmat.m[7]
				+ rmat.m[4] * rmat.m[1] * rmat.m[11]
				- rmat.m[0] * rmat.m[5] * rmat.m[11]) * invDet;
		}
	};
}

#endif