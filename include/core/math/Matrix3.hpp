#ifndef MATRIX3_HPP
#define MATRIX3_HPP

#include "Precision.hpp"
#include "Vector3.hpp"
#include "Quaternion.hpp"

class Matrix3 {

public:
	Real m[9]; //TODO dodaj komentarje za vse operacije

	Matrix3(const Real &v = 1.0f)
	{
		m[0] = m[4] = m[8] = v; // diagonal elements
		m[1] = m[2] = m[3] = m[5] = m[6] = m[7] = 0.0f;
	}

	Matrix3(const Real &a00, const Real &a01, const Real &a02,
		const Real &a10, const Real &a11, const Real &a12,
		const Real &a20, const Real &a21, const Real &a22)
	{
		m[0] = a00;		m[1] = a01;		m[2] = a02;
		m[3] = a10;		m[4] = a11;		m[5] = a12;
		m[6] = a20;		m[7] = a21;		m[8] = a22;
	}

	Matrix3 operator*(const Real &_value) const
	{
		return Matrix3(
			m[0] * _value, m[1] * _value, m[2] * _value,
			m[3] * _value, m[4] * _value, m[5] * _value,
			m[6] * _value, m[7] * _value, m[8] * _value
			);
	}

	Matrix3 operator*(const Matrix3 &_rmat) const
	{
		return Matrix3(
			m[0] * _rmat.m[0] + m[1] * _rmat.m[3] + m[2] * _rmat.m[6],
			m[0] * _rmat.m[1] + m[1] * _rmat.m[4] + m[2] * _rmat.m[7],
			m[0] * _rmat.m[2] + m[1] * _rmat.m[5] + m[2] * _rmat.m[8],

			m[3] * _rmat.m[0] + m[4] * _rmat.m[3] + m[5] * _rmat.m[6],
			m[3] * _rmat.m[1] + m[4] * _rmat.m[4] + m[5] * _rmat.m[7],
			m[3] * _rmat.m[2] + m[4] * _rmat.m[5] + m[5] * _rmat.m[8],

			m[6] * _rmat.m[0] + m[7] * _rmat.m[3] + m[8] * _rmat.m[6],
			m[6] * _rmat.m[1] + m[7] * _rmat.m[4] + m[8] * _rmat.m[7],
			m[6] * _rmat.m[2] + m[7] * _rmat.m[5] + m[8] * _rmat.m[8]
			);
	}

	Matrix3 operator+(const Matrix3 &_rmat) const
	{
		return Matrix3(
			m[0] + _rmat.m[0], m[1] + _rmat.m[1], m[2] + _rmat.m[2],
			m[3] + _rmat.m[3], m[4] + _rmat.m[4], m[5] + _rmat.m[5],
			m[6] + _rmat.m[6], m[7] + _rmat.m[7], m[8] + _rmat.m[8]
			);
	}

	Vector3r operator*(const Vector3r &_vector) const
	{
		return Vector3r(
			_vector.x * m[0] + _vector.y * m[1] + _vector.z * m[2],
			_vector.x * m[3] + _vector.y * m[4] + _vector.z * m[5],
			_vector.x * m[6] + _vector.y * m[7] + _vector.z * m[8]);
	}

	void operator*=(const Real &_value) {
		m[0] *= _value;
		m[1] *= _value;
		m[2] *= _value;
			
		m[3] *= _value;
		m[4] *= _value;
		m[5] *= _value;
			
		m[6] *= _value;
		m[7] *= _value;
		m[8] *= _value;
	}

	void operator*=(const Matrix3 &_rmat) {
		Real v1, v2, v3;
		v1 = m[0] * _rmat.m[0] + m[1] * _rmat.m[3] + m[2] * _rmat.m[6];
		v2 = m[0] * _rmat.m[1] + m[1] * _rmat.m[4] + m[2] * _rmat.m[7];
		v3 = m[0] * _rmat.m[2] + m[1] * _rmat.m[5] + m[2] * _rmat.m[8];
		m[0] = v1;
		m[1] = v2;
		m[2] = v3;

		v1 = m[3] * _rmat.m[0] + m[4] * _rmat.m[3] + m[5] * _rmat.m[6];
		v2 = m[3] * _rmat.m[1] + m[4] * _rmat.m[4] + m[5] * _rmat.m[7];
		v3 = m[3] * _rmat.m[2] + m[4] * _rmat.m[5] + m[5] * _rmat.m[8];
		m[3] = v1;
		m[4] = v2;
		m[5] = v3;

		v1 = m[6] * _rmat.m[0] + m[7] * _rmat.m[3] + m[8] * _rmat.m[6];
		v2 = m[6] * _rmat.m[1] + m[7] * _rmat.m[4] + m[8] * _rmat.m[7];
		v3 = m[6] * _rmat.m[2] + m[7] * _rmat.m[5] + m[8] * _rmat.m[8];
		m[6] = v1;
		m[7] = v2;
		m[8] = v3;
	}

	void operator+=(const Matrix3 &_rmat) {
		m[0] += _rmat.m[0];
		m[1] += _rmat.m[1];
		m[2] += _rmat.m[2];

		m[3] += _rmat.m[3];
		m[4] += _rmat.m[4];
		m[5] += _rmat.m[5];

		m[6] += _rmat.m[6];
		m[7] += _rmat.m[7];
		m[8] += _rmat.m[8];
	}

	Vector3r transform(const Vector3r &_vector) const
	{
		return (*this) * _vector;
	}

	Real getDeterminant() const
	{
		return getDeterminant(*this);
	}

	Matrix3 inverse() const
	{
		Matrix3 result;
		result.setInverse(*this);
		return result;
	}

	void invert()
	{
		Matrix3 result;
		result.setInverse(*this);
		*this = result;
	}
		
	Matrix3 transpose() const
	{
		Matrix3 result;
		result.setTranspose(*this);
		return result;
	}

	void setOrientation(const Quarternion &q)
	{
		m[0] = 1 - (2 * q.j * q.j + 2 * q.k * q.k);
		m[1] = 2 * q.i * q.j + 2 * q.k * q.r;
		m[2] = 2 * q.i * q.k - 2 * q.j * q.r;

		m[3] = 2 * q.i * q.j - 2 * q.k * q.r;
		m[4] = 1 - (2 * q.i * q.i + 2 * q.k * q.k);
		m[5] = 2 * q.j * q.k + 2 * q.i * q.r;

		m[6] = 2 * q.i * q.k + 2 * q.j * q.r;
		m[7] = 2 * q.j * q.k - 2 * q.i * q.r;
		m[8] = 1 - (2 * q.i * q.i + 2 * q.j * q.j);
	}

private:
	Real getDeterminant(const Matrix3 &_rmat) const
	{
		Real v1 = _rmat.m[0] * _rmat.m[4] * _rmat.m[8];
		Real v2 = _rmat.m[1] * _rmat.m[5] * _rmat.m[6];
		Real v3 = _rmat.m[2] * _rmat.m[3] * _rmat.m[7];

		Real v4 = _rmat.m[6] * _rmat.m[4] * _rmat.m[2];
		Real v5 = _rmat.m[7] * _rmat.m[5] * _rmat.m[0];
		Real v6 = _rmat.m[8] * _rmat.m[3] * _rmat.m[1];

		return v1 + v2 + v3 - v4 - v5 - v6;
	}

	void setTranspose(const Matrix3 &_rmat) {
		m[0] = _rmat.m[0]; m[1] = _rmat.m[3]; m[2] = _rmat.m[6];
		m[3] = _rmat.m[1]; m[4] = _rmat.m[4]; m[5] = _rmat.m[7];
		m[6] = _rmat.m[2]; m[7] = _rmat.m[5]; m[8] = _rmat.m[8];
	}

	void setInverse(const Matrix3 &_rmat)
	{
		Real det = getDeterminant(_rmat);

		if (det == 0.0f) return;
		Real invDet = 1.0f / det;

		m[0] = (_rmat.m[4] * _rmat.m[8] - _rmat.m[7] * _rmat.m[5]) * invDet;
		m[1] = -(_rmat.m[1] * _rmat.m[8] - _rmat.m[2] * _rmat.m[7]) * invDet;
		m[2] = (_rmat.m[1] * _rmat.m[5] - _rmat.m[2] * _rmat.m[4]) * invDet;

		m[3] = -(_rmat.m[3] * _rmat.m[8] - _rmat.m[5] * _rmat.m[6]) * invDet;
		m[4] = (_rmat.m[0] * _rmat.m[8] - _rmat.m[2] * _rmat.m[6]) * invDet;
		m[5] = -(_rmat.m[0] * _rmat.m[5] - _rmat.m[2] * _rmat.m[3])* invDet;

		m[6] = (_rmat.m[3] * _rmat.m[7] - _rmat.m[4] * _rmat.m[6]) * invDet;
		m[7] = -(_rmat.m[0] * _rmat.m[7] - _rmat.m[1] * _rmat.m[6]) * invDet;
		m[8] = (_rmat.m[0] * _rmat.m[4] - _rmat.m[1] * _rmat.m[3]) * invDet;
	}
};
#endif