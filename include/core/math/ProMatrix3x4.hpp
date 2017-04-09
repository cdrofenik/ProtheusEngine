#ifndef PROMETHEUS_MATRIX3X4_HPP
#define PROMETHEUS_MATRIX3X4_HPP

#include "ProVector3.hpp"
#include "ProQuaternion.hpp"

class ProMatrix3x4
{
public:
	ProReal m[12]; //TODO dodaj komentarje za vse operacije

	ProMatrix3x4(const ProReal& v = 1.0f)
	{
		m[0] = m[5] = m[10] = v; // diagonal elements
		m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = 0.0f;
	}

	ProMatrix3x4(const ProReal& a0, const ProReal& a1, const ProReal& a2, const ProReal& a3,
		const ProReal& a4, const ProReal& a5, const ProReal& a6, const ProReal& a7,
		const ProReal& a8, const ProReal& a9, const ProReal& a10, const ProReal& a11)
	{
		m[0] = a0; m[1] = a1; m[2] = a2; m[3] = a3;
		m[4] = a4; m[5] = a5; m[6] = a6; m[7] = a7;
		m[8] = a8; m[9] = a9; m[10] = a10; m[11] = a11;
	}

	ProVector3r operator*(const ProVector3r& _vector) const
	{
		return ProVector3r(
			_vector.x * m[0] + _vector.y * m[1] + _vector.z * m[2] + m[3],
			_vector.x * m[4] + _vector.y * m[5] + _vector.z * m[6] + m[7],
			_vector.x * m[8] + _vector.y * m[9] + _vector.z * m[10] + m[11]
			);
	}

	ProMatrix3x4 operator*(const ProMatrix3x4& _rmat) const
	{
		return ProMatrix3x4(
			m[0] * _rmat.m[0] + m[1] * _rmat.m[4] + m[2] * _rmat.m[8],
			m[0] * _rmat.m[1] + m[1] * _rmat.m[5] + m[2] * _rmat.m[9],
			m[0] * _rmat.m[2] + m[1] * _rmat.m[6] + m[2] * _rmat.m[10],
			m[0] * _rmat.m[3] + m[1] * _rmat.m[7] + m[2] * _rmat.m[11] + m[3],

			m[4] * _rmat.m[0] + m[5] * _rmat.m[4] + m[6] * _rmat.m[8],
			m[4] * _rmat.m[1] + m[5] * _rmat.m[5] + m[6] * _rmat.m[9],
			m[4] * _rmat.m[2] + m[5] * _rmat.m[6] + m[6] * _rmat.m[10],
			m[4] * _rmat.m[3] + m[5] * _rmat.m[7] + m[6] * _rmat.m[11] + m[7],

			m[8] * _rmat.m[0] + m[9] * _rmat.m[4] + m[10] * _rmat.m[8],
			m[8] * _rmat.m[1] + m[9] * _rmat.m[5] + m[10] * _rmat.m[9],
			m[8] * _rmat.m[2] + m[9] * _rmat.m[6] + m[10] * _rmat.m[10],
			m[8] * _rmat.m[3] + m[9] * _rmat.m[7] + m[10] * _rmat.m[11] + m[11]
			);
	}

	void operator*=(const ProMatrix3x4& _rmat)
	{
		ProReal v1, v2, v3, v4;
		v1 = m[0] * _rmat.m[0] + m[1] * _rmat.m[4] + m[2] * _rmat.m[8];
		v2 = m[0] * _rmat.m[1] + m[1] * _rmat.m[5] + m[2] * _rmat.m[9];
		v3 = m[0] * _rmat.m[2] + m[1] * _rmat.m[6] + m[2] * _rmat.m[10];
		v4 = m[0] * _rmat.m[3] + m[1] * _rmat.m[7] + m[2] * _rmat.m[11] + m[3];
		m[0] = v1;
		m[1] = v2;
		m[2] = v3;
		m[3] = v4;

		v1 = m[4] * _rmat.m[0] + m[5] * _rmat.m[4] + m[6] * _rmat.m[8];
		v2 = m[4] * _rmat.m[1] + m[5] * _rmat.m[5] + m[6] * _rmat.m[9];
		v3 = m[4] * _rmat.m[2] + m[5] * _rmat.m[6] + m[6] * _rmat.m[10];
		v4 = m[4] * _rmat.m[3] + m[5] * _rmat.m[7] + m[6] * _rmat.m[11] + m[7];
		m[4] = v1;
		m[5] = v2;
		m[6] = v3;
		m[7] = v4;

		v1 = m[8] * _rmat.m[0] + m[9] * _rmat.m[4] + m[10] * _rmat.m[8];
		v2 = m[8] * _rmat.m[1] + m[9] * _rmat.m[5] + m[10] * _rmat.m[9];
		v3 = m[8] * _rmat.m[2] + m[9] * _rmat.m[6] + m[10] * _rmat.m[10];
		v4 = m[8] * _rmat.m[3] + m[9] * _rmat.m[7] + m[10] * _rmat.m[11] + m[11];
		m[8] = v1;
		m[9] = v2;
		m[10] = v3;
		m[11] = v4;
	}

	ProVector3r transform(const ProVector3r& _vector) const
	{
		return (*this) * _vector;
	}

	ProReal getDeterminant() const
	{
		return getDeterminant(*this);
	}

	ProMatrix3x4 inverse() const
	{
		ProMatrix3x4 result;
		result.setInverse(*this);
		return result;
	}

	void invert()
	{
		ProMatrix3x4 result;
		result.setInverse(*this);
		*this = result;
	}

	void setOrientation(const ProQuarternion &_q, const ProVector3r &_pos)
	{
		m[0] = 1 - (2 * _q.j * _q.j + 2 * _q.k * _q.k);
		m[1] = 2 * _q.i * _q.j + 2 * _q.k * _q.r;
		m[2] = 2 * _q.i * _q.k - 2 * _q.j * _q.r;
		m[3] = _pos.x;

		m[4] = 2 * _q.i * _q.j - 2 * _q.k * _q.r;
		m[5] = 1 - (2 * _q.i * _q.i + 2 * _q.k * _q.k);
		m[6] = 2 * _q.j * _q.k + 2 * _q.i * _q.r;
		m[7] = _pos.y;

		m[8] = 2 * _q.i * _q.k + 2 * _q.j * _q.r;
		m[9] = 2 * _q.j * _q.k - 2 * _q.i * _q.r;
		m[10] = 1 - (2 * _q.i * _q.i + 2 * _q.j * _q.j);
		m[11] = _pos.z;
	}

	ProVector3r transformInverse(const ProVector3r &_vector) const
	{
		ProVector3r tmp = _vector;
		tmp.x -= m[3];
		tmp.y -= m[7];
		tmp.z -= m[11];
		return ProVector3r(
			tmp.x * m[0] + tmp.y * m[4] + tmp.z * m[8],
			tmp.x * m[1] + tmp.y * m[5] + tmp.z * m[9],
			tmp.x * m[2] + tmp.y * m[6] + tmp.z * m[10]
			);
	}

	ProVector3r getAxisValues(const unsigned int &_axis) const
	{
		return ProVector3r(m[_axis], m[_axis + 4], m[_axis + 8]);
	}
	
private:
	ProReal getDeterminant(const ProMatrix3x4 &_rmat) const
	{
		ProReal v1 = _rmat.m[0] * _rmat.m[5] * _rmat.m[10];
		ProReal v2 = _rmat.m[8] * _rmat.m[1] * _rmat.m[6];
		ProReal v3 = _rmat.m[4] * _rmat.m[9] * _rmat.m[2];

		ProReal v4 = _rmat.m[8] * _rmat.m[5] * _rmat.m[2];
		ProReal v5 = _rmat.m[0] * _rmat.m[9] * _rmat.m[6];
		ProReal v6 = _rmat.m[4] * _rmat.m[1] * _rmat.m[10];

		return v1 + v2 + v3 - v4 - v5 - v6;
	}

	void setInverse(const ProMatrix3x4 &_rmat)
	{
		ProReal det = getDeterminant(_rmat);

		if (det == 0.0f) return;
		ProReal invDet = 1.0f / det;

		m[0] = (-_rmat.m[9] * _rmat.m[6] + _rmat.m[5] * _rmat.m[10]) * invDet;
		m[1] = (_rmat.m[9] * _rmat.m[2] - _rmat.m[1] * _rmat.m[10]) * invDet;
		m[2] = (-_rmat.m[5] * _rmat.m[2] + _rmat.m[1] * _rmat.m[6]) * invDet;

		m[3] = (_rmat.m[9] * _rmat.m[6] * _rmat.m[3]
			- _rmat.m[5] * _rmat.m[10] * _rmat.m[3]
			- _rmat.m[9] * _rmat.m[2] * _rmat.m[7]
			+ _rmat.m[1] * _rmat.m[10] * _rmat.m[7]
			+ _rmat.m[5] * _rmat.m[2] * _rmat.m[11]
			- _rmat.m[1] * _rmat.m[6] * _rmat.m[11]) * invDet;

		m[4] = (_rmat.m[8] * _rmat.m[6] - _rmat.m[4] * _rmat.m[10]) * invDet;
		m[5] = (-_rmat.m[8] * _rmat.m[2] + _rmat.m[0] * _rmat.m[10]) * invDet;
		m[6] = (+_rmat.m[4] * _rmat.m[2] - _rmat.m[0] * _rmat.m[6]) * invDet;

		m[7] = (_rmat.m[8] * _rmat.m[6] * _rmat.m[3]
			- _rmat.m[4] * _rmat.m[10] * _rmat.m[3]
			- _rmat.m[8] * _rmat.m[2] * _rmat.m[7]
			+ _rmat.m[0] * _rmat.m[10] * _rmat.m[7]
			+ _rmat.m[4] * _rmat.m[2] * _rmat.m[11]
			- _rmat.m[0] * _rmat.m[6] * _rmat.m[11]) * invDet;

		m[8] = (-_rmat.m[8] * _rmat.m[5] + _rmat.m[4] * _rmat.m[9]) * invDet;
		m[9] = (_rmat.m[8] * _rmat.m[1] + _rmat.m[0] * _rmat.m[9]) * invDet;
		m[10] = (-_rmat.m[4] * _rmat.m[1] - _rmat.m[0] * _rmat.m[5]) * invDet;

		m[11] = (_rmat.m[8] * _rmat.m[5] * _rmat.m[3]
			- _rmat.m[4] * _rmat.m[9] * _rmat.m[3]
			- _rmat.m[8] * _rmat.m[1] * _rmat.m[7]
			+ _rmat.m[0] * _rmat.m[9] * _rmat.m[7]
			+ _rmat.m[4] * _rmat.m[1] * _rmat.m[11]
			- _rmat.m[0] * _rmat.m[5] * _rmat.m[11]) * invDet;
	}

};
#endif