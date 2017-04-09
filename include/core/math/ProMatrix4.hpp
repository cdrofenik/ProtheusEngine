#ifndef PROMETHEUS_MATRIX4_HPP
#define PROMETHEUS_MATRIX4_HPP

#include "ProMatrix3.hpp"
#include "ProMatrix3x4.hpp"

class ProMatrix4 {

public:
	ProReal m[16]; //TODO: Dodaj komentarje za funckije

	ProMatrix4(const ProReal& v = 1.0f) {
		m[0] = m[5] = m[10] = v; // Diagonal elements
		m[15] = 1.0f; //homogeneous

		m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] =
			m[11] = m[12] = m[13] = m[14] = 0.0f;
	}

	ProMatrix4(const ProMatrix3& _matrix3) {
		m[0] = _matrix3.m[0];
		m[1] = _matrix3.m[1];
		m[2] = _matrix3.m[2];
		m[4] = _matrix3.m[3];
		m[5] = _matrix3.m[4];
		m[6] = _matrix3.m[5];
		m[8] = _matrix3.m[6];
		m[9] = _matrix3.m[7];
		m[10] = _matrix3.m[8];
		m[15] = 1; //homogeneous
		m[11] = m[7] = m[3] = m[12] = m[13] = m[14] = 0;
	}

	ProMatrix4(const ProMatrix3x4& _matrix3x4) {
		m[0] = _matrix3x4.m[0];
		m[1] = _matrix3x4.m[1];
		m[2] = _matrix3x4.m[2];
		m[3] = _matrix3x4.m[3];
		m[4] = _matrix3x4.m[4];
		m[5] = _matrix3x4.m[5];
		m[6] = _matrix3x4.m[6];
		m[7] = _matrix3x4.m[7];
		m[8] = _matrix3x4.m[8];
		m[9] = _matrix3x4.m[9];
		m[10] = _matrix3x4.m[10];
		m[11] = _matrix3x4.m[11];
		m[12] = m[13] = m[14] = 0;
		m[15] = 1;
	}

	ProMatrix4(const ProReal& a0, const ProReal& a1, const ProReal& a2, const ProReal& a3,
		const ProReal& a4, const ProReal& a5, const ProReal& a6, const ProReal& a7,
		const ProReal& a8, const ProReal& a9, const ProReal& a10, const ProReal& a11,
		const ProReal& a12, const ProReal& a13, const ProReal& a14, const ProReal& a15)
	{
		m[0] = a0; m[1] = a1; m[2] = a2; m[3] = a3;
		m[4] = a4; m[5] = a5; m[6] = a6; m[7] = a7;
		m[8] = a8; m[9] = a9; m[10] = a10; m[11] = a11;
		m[12] = a12; m[13] = a13; m[14] = a14; m[15] = a15;
	}

	ProMatrix4 operator*(const ProMatrix4& _rmat) const
	{
		return ProMatrix4(
			m[0] * _rmat.m[0] + m[1] * _rmat.m[4] + m[2] * _rmat.m[8] + m[2] * _rmat.m[12],
			m[0] * _rmat.m[1] + m[1] * _rmat.m[5] + m[2] * _rmat.m[9] + m[2] * _rmat.m[13],
			m[0] * _rmat.m[2] + m[1] * _rmat.m[6] + m[2] * _rmat.m[10] + m[2] * _rmat.m[14],
			m[0] * _rmat.m[3] + m[1] * _rmat.m[7] + m[2] * _rmat.m[11] + m[2] * _rmat.m[15],

			m[4] * _rmat.m[0] + m[5] * _rmat.m[4] + m[6] * _rmat.m[8] + m[7] * _rmat.m[12],
			m[4] * _rmat.m[1] + m[5] * _rmat.m[5] + m[6] * _rmat.m[9] + m[7] * _rmat.m[13],
			m[4] * _rmat.m[2] + m[5] * _rmat.m[6] + m[6] * _rmat.m[10] + m[7] * _rmat.m[14],
			m[4] * _rmat.m[3] + m[5] * _rmat.m[7] + m[6] * _rmat.m[11] + m[7] * _rmat.m[15],

			m[8] * _rmat.m[0] + m[9] * _rmat.m[4] + m[10] * _rmat.m[8] + m[11] * _rmat.m[12],
			m[8] * _rmat.m[1] + m[9] * _rmat.m[5] + m[10] * _rmat.m[9] + m[11] * _rmat.m[13],
			m[8] * _rmat.m[2] + m[9] * _rmat.m[6] + m[10] * _rmat.m[10] + m[11] * _rmat.m[14],
			m[8] * _rmat.m[3] + m[9] * _rmat.m[7] + m[10] * _rmat.m[11] + m[11] * _rmat.m[15],

			m[12] * _rmat.m[0] + m[13] * _rmat.m[4] + m[14] * _rmat.m[8] + m[15] * _rmat.m[12],
			m[12] * _rmat.m[1] + m[13] * _rmat.m[5] + m[14] * _rmat.m[9] + m[15] * _rmat.m[13],
			m[12] * _rmat.m[2] + m[13] * _rmat.m[6] + m[14] * _rmat.m[10] + m[15] * _rmat.m[14],
			m[12] * _rmat.m[3] + m[13] * _rmat.m[7] + m[14] * _rmat.m[11] + m[15] * _rmat.m[15]
			);
	}

	ProMatrix4 operator+(const ProMatrix4& _rmat) const
	{

		return ProMatrix4(
			m[0] + _rmat.m[0], m[1] + _rmat.m[1], m[2] + _rmat.m[2], m[3] + _rmat.m[3],
			m[4] + _rmat.m[4], m[5] + _rmat.m[5], m[6] + _rmat.m[6], m[7] + _rmat.m[7],
			m[8] + _rmat.m[8], m[9] + _rmat.m[9], m[10] + _rmat.m[10], m[11] + _rmat.m[11],
			m[12] + _rmat.m[12], m[13] + _rmat.m[13], m[14] + _rmat.m[14], m[15] + _rmat.m[15]
			);
	}

	//TODO: Extend for +=, *=

	ProMatrix4 transpose() {
		ProMatrix4 result;
		result.m[0] = m[0];		result.m[1] = m[4];		result.m[2] = m[8];		result.m[3] = m[12];
		result.m[4] = m[1];		result.m[5] = m[5];		result.m[6] = m[9];		result.m[7] = m[13];
		result.m[8] = m[2];		result.m[9] = m[6];		result.m[10] = m[10];	result.m[11] = m[14];
		result.m[12] = m[3];	result.m[13] = m[7];	result.m[14] = m[11];	result.m[15] = m[15];

		return result;
	}
};
#endif