#ifndef MATRIX4_HPP
#define MATRIX4_HPP

#include "Matrix3.hpp"
#include "Matrix3x4.hpp"

namespace math {

	class Matrix4 {

	public:
		Real m[16]; //TODO: Dodaj komentarje za funckije

		Matrix4(const Real& v = 1.0f) {
			m[0] = m[5] = m[10] = v; // Diagonal elements
			m[15] = 1.0f; //homogeneous

			m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] =
				m[11] = m[12] = m[13] = m[14] = 0.0f;
		}

		Matrix4(const Matrix3& matrix3) {
			m[0] = matrix3.m[0];
			m[1] = matrix3.m[1];
			m[2] = matrix3.m[2];
			m[4] = matrix3.m[3];
			m[5] = matrix3.m[4];
			m[6] = matrix3.m[5];
			m[8] = matrix3.m[6];
			m[9] = matrix3.m[7];
			m[10] = matrix3.m[8];
			m[15] = 1; //homogeneous
			m[11] = m[7] = m[3] = m[12] = m[13] = m[14] = 0;
		}

		Matrix4(const Matrix3x4& matrix3x4) {
			m[0] = matrix3x4.m[0];
			m[1] = matrix3x4.m[1];
			m[2] = matrix3x4.m[2];
			m[3] = matrix3x4.m[3];
			m[4] = matrix3x4.m[4];
			m[5] = matrix3x4.m[5];
			m[6] = matrix3x4.m[6];
			m[7] = matrix3x4.m[7];
			m[8] = matrix3x4.m[8];
			m[9] = matrix3x4.m[9];
			m[10] = matrix3x4.m[10];
			m[11] = matrix3x4.m[11];
			m[12] = m[13] = m[14] = 0;
			m[15] = 1;
		}

		Matrix4(const Real& a0, const Real& a1, const Real& a2, const Real& a3,
			const Real& a4, const Real& a5, const Real& a6, const Real& a7,
			const Real& a8, const Real& a9, const Real& a10, const Real& a11,
			const Real& a12, const Real& a13, const Real& a14, const Real& a15)
		{
			m[0] = a0; m[1] = a1; m[2] = a2; m[3] = a3;
			m[4] = a4; m[5] = a5; m[6] = a6; m[7] = a7;
			m[8] = a8; m[9] = a9; m[10] = a10; m[11] = a11;
			m[12] = a12; m[13] = a13; m[14] = a14; m[15] = a15;
		}

		Matrix4 operator*(const Matrix4& rmat) const
		{
			return Matrix4(
				m[0] * rmat.m[0] + m[1] * rmat.m[4] + m[2] * rmat.m[8] + m[3] * rmat.m[12],
				m[0] * rmat.m[1] + m[1] * rmat.m[5] + m[2] * rmat.m[9] + m[3] * rmat.m[13],
				m[0] * rmat.m[2] + m[1] * rmat.m[6] + m[2] * rmat.m[10] + m[3] * rmat.m[14],
				m[0] * rmat.m[3] + m[1] * rmat.m[7] + m[2] * rmat.m[11] + m[3] * rmat.m[15],

				m[4] * rmat.m[0] + m[5] * rmat.m[4] + m[6] * rmat.m[8] + m[7] * rmat.m[12],
				m[4] * rmat.m[1] + m[5] * rmat.m[5] + m[6] * rmat.m[9] + m[7] * rmat.m[13],
				m[4] * rmat.m[2] + m[5] * rmat.m[6] + m[6] * rmat.m[10] + m[7] * rmat.m[14],
				m[4] * rmat.m[3] + m[5] * rmat.m[7] + m[6] * rmat.m[11] + m[7] * rmat.m[15],

				m[8] * rmat.m[0] + m[9] * rmat.m[4] + m[10] * rmat.m[8] + m[11] * rmat.m[12],
				m[8] * rmat.m[1] + m[9] * rmat.m[5] + m[10] * rmat.m[9] + m[11] * rmat.m[13],
				m[8] * rmat.m[2] + m[9] * rmat.m[6] + m[10] * rmat.m[10] + m[11] * rmat.m[14],
				m[8] * rmat.m[3] + m[9] * rmat.m[7] + m[10] * rmat.m[11] + m[11] * rmat.m[15],

				m[12] * rmat.m[0] + m[13] * rmat.m[4] + m[14] * rmat.m[8] + m[15] * rmat.m[12],
				m[12] * rmat.m[1] + m[13] * rmat.m[5] + m[14] * rmat.m[9] + m[15] * rmat.m[13],
				m[12] * rmat.m[2] + m[13] * rmat.m[6] + m[14] * rmat.m[10] + m[15] * rmat.m[14],
				m[12] * rmat.m[3] + m[13] * rmat.m[7] + m[14] * rmat.m[11] + m[15] * rmat.m[15]
			);
		}

		Matrix4 operator+(const Matrix4& rmat) const
		{

			return Matrix4(
				m[0] + rmat.m[0], m[1] + rmat.m[1], m[2] + rmat.m[2], m[3] + rmat.m[3],
				m[4] + rmat.m[4], m[5] + rmat.m[5], m[6] + rmat.m[6], m[7] + rmat.m[7],
				m[8] + rmat.m[8], m[9] + rmat.m[9], m[10] + rmat.m[10], m[11] + rmat.m[11],
				m[12] + rmat.m[12], m[13] + rmat.m[13], m[14] + rmat.m[14], m[15] + rmat.m[15]
			);
		}

		//TODO: Extend for +=, *=

		Matrix4 transpose() {
			Matrix4 result;
			result.m[0] = m[0];		result.m[1] = m[4];		result.m[2] = m[8];		result.m[3] = m[12];
			result.m[4] = m[1];		result.m[5] = m[5];		result.m[6] = m[9];		result.m[7] = m[13];
			result.m[8] = m[2];		result.m[9] = m[6];		result.m[10] = m[10];	result.m[11] = m[14];
			result.m[12] = m[3];	result.m[13] = m[7];	result.m[14] = m[11];	result.m[15] = m[15];

			return result;
		}
	};
}

#endif