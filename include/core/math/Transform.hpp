#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "Vector3.hpp"
#include "Matrix4.hpp"

//system directory
#include <math.h>
	
namespace math {

	class Transform
	{
	public:
		Transform() {
			m_scale = Vector3r(1.0f, 1.0f, 1.0f);
			m_origin = Vector3r(0.0f, 0.0f, 0.0f);
			m_translation = Vector3r(0.0f, 0.0f, 0.0f);
		}

		~Transform() { }

		void setScale(const Real& x, const Real& y, const Real& z) {
			m_scale = Vector3r(x, y, z);
			m_wasChanged = true;
		}

		void setOrigin(const Real& x, const Real& y, const Real& z) {
			m_origin = Vector3r(x, y, z);
			m_wasChanged = true;
		}

		void setRotation(const Real& alfaX, const Real& alfaY, const Real& alfaZ) {
			m_rotation = Vector3r(alfaX, alfaY, alfaZ);
			m_wasChanged = true;
		}

		void setTranslation(const Real& x, const Real& y, const Real& z) {
			m_translation = Vector3r(x, y, z);
			m_wasChanged = true;
		}

		/*
		Returns Model matrix which can be manipulated through setScale, setOrigin and setRotation
		*/
		Matrix4 getTransformMatrix() {
			if (m_wasChanged) {
				m_finalTransformation = getTranslationMatrix() * getRotationMatrix() * getScaleMatrix();
				m_wasChanged = false;
			}

			return m_finalTransformation;
		}

		static Matrix4 projectionMatrix(const Real& fov, const Real& ratio, const Real& zNear, const Real& zFar) {
			Matrix4 v;

			Real tanHalfFOV = (Real)tan(fov / 2);
			Real zRange = zFar - zNear;

			v.m[0] = 1.0f / (tanHalfFOV * ratio);	v.m[1] = 0.0f;				v.m[2] = 0.0f;						v.m[3] = 0.0f;
			v.m[4] = 0.0f;							v.m[5] = 1.0f / tanHalfFOV;	v.m[6] = 0.0f;						v.m[7] = 0.0f;
			v.m[8] = 0.0f;							v.m[9] = 0.0f;				v.m[10] = -(zFar + zNear) / zRange;	v.m[11] = -(2.0f * zFar * zNear) / zRange;
			v.m[12] = 0.0f;							v.m[13] = 0.0f;				v.m[14] = -1.0f;					v.m[15] = 0.0f;
			return v;
		}

		static Matrix4 lookAtMatrix(const Vector3r& position, const Vector3r& target, const Vector3r& up) {
			Vector3r zAxis = (position - target).normalize();
			Vector3r xAxis = (up % zAxis).normalize();
			Vector3r yAxis = zAxis % xAxis;

			Matrix4 Ruvw = Matrix4(
				xAxis.x, xAxis.y, xAxis.z, 0,
				yAxis.x, yAxis.y, yAxis.z, 0,
				zAxis.x, zAxis.y, zAxis.z, 0,
				0, 0, 0, 1
			);

			Matrix4 translationToEye(
				1, 0, 0, -position.x,
				0, 1, 0, -position.y,
				0, 0, 1, -position.z,
				0, 0, 0, 1
			);

			return Ruvw * translationToEye;
		}

		static Vector3r& rotate(const Real& angle, const Vector3r& axis)
		{
			Real sinHalfAngle = (Real)sin(angle / 2);
			Real cosHalfAngle = (Real)cos(angle / 2);

			Real rX = axis.x * sinHalfAngle;
			Real rY = axis.y * sinHalfAngle;
			Real rZ = axis.z * sinHalfAngle;
			Real rW = cosHalfAngle;

			Quarternion rotation(rX, rY, rZ, rW);
			Quarternion w = rotation.rotateByVector(axis);

			Vector3r result(w.i, w.j, w.k);

			return result;
		}

	private:
		bool m_wasChanged = false;
		Vector3r m_scale;
		Vector3r m_rotation;
		Vector3r m_origin;
		Vector3r m_translation;
		Matrix4 m_finalTransformation;

		Matrix4 getTranslationMatrix() {
			Matrix4 v;
			v.m[0] = 1.0f;	v.m[1] = 0.0f;	v.m[2] = 0.0f;	v.m[12] = 0.0f;
			v.m[4] = 0.0f;	v.m[5] = 1.0f;	v.m[6] = 0.0f;	v.m[13] = 0.0f;
			v.m[8] = 0.0f;	v.m[9] = 0.0f;	v.m[10] = 1.0f;	v.m[14] = 0.0f;
			v.m[3] = m_origin.x + m_translation.x;
			v.m[7] = m_origin.y + m_translation.y;
			v.m[11] = m_origin.z + m_translation.z;
			v.m[15] = 1.0f;

			return v;
		}

		Matrix4 getScaleMatrix() {
			Matrix4 v;
			v.m[0] = m_scale.x;	v.m[1] = 0.0f;		v.m[2] = 0.0f;		v.m[3] = 0.0f;
			v.m[4] = 0.0f;		v.m[5] = m_scale.y;	v.m[6] = 0.0f;		v.m[7] = 0.0f;
			v.m[8] = 0.0f;		v.m[9] = 0.0f;		v.m[10] = m_scale.z;	v.m[11] = 0.0f;
			v.m[12] = 0.0f;		v.m[13] = 0.0f;		v.m[14] = 0.0f;		v.m[15] = 1.0f;
			return v;
		}

		Matrix4 getRotationMatrix() {
			Matrix4 v;

			//Rotation around z
			Matrix4 aroundZ;
			aroundZ.m[0] = cosf(m_rotation.z);	aroundZ.m[1] = -sinf(m_rotation.z);	aroundZ.m[2] = 0.0f;	aroundZ.m[3] = 0.0f;
			aroundZ.m[4] = sinf(m_rotation.z);	aroundZ.m[5] = cosf(m_rotation.z);	aroundZ.m[6] = 0.0f;	aroundZ.m[7] = 0.0f;
			aroundZ.m[8] = 0.0f;				aroundZ.m[9] = 0.0f;				aroundZ.m[10] = 1.0f;	aroundZ.m[11] = 0.0f;
			aroundZ.m[12] = 0.0f;				aroundZ.m[13] = 0.0f;				aroundZ.m[14] = 0.0f;	aroundZ.m[15] = 1.0f;

			//Rotation around y
			Matrix4 aroundY;
			aroundY.m[0] = cosf(m_rotation.y);	aroundY.m[1] = 0.0f;	aroundY.m[2] = -sinf(m_rotation.y);	aroundY.m[3] = 0.0f;
			aroundY.m[4] = 0.0f;				aroundY.m[5] = 1.0f;	aroundY.m[6] = 0.0f;				aroundY.m[7] = 0.0f;
			aroundY.m[8] = sinf(m_rotation.y);	aroundY.m[9] = 0.0f;	aroundY.m[10] = cosf(m_rotation.y);	aroundY.m[11] = 0.0f;
			aroundY.m[12] = 0.0f;				aroundY.m[13] = 0.0f;	aroundY.m[14] = 0.0f;				aroundY.m[15] = 1.0f;

			//Rotation around x
			Matrix4 aroundX;
			aroundX.m[0] = 1.0f;	aroundX.m[1] = 0.0f;				aroundX.m[2] = 0.0f;				aroundX.m[3] = 0.0f;
			aroundX.m[4] = 0.0f;	aroundX.m[5] = cosf(m_rotation.x);	aroundX.m[6] = sinf(m_rotation.x);	aroundX.m[7] = 0.0f;
			aroundX.m[8] = 0.0f;	aroundX.m[9] = -sinf(m_rotation.x);	aroundX.m[10] = cosf(m_rotation.x);	aroundX.m[11] = 0.0f;
			aroundX.m[12] = 0.0f;	aroundX.m[13] = 0.0f;				aroundX.m[14] = 0.0f;				aroundX.m[15] = 1.0f;

			v = aroundZ * aroundY * aroundX;
			return v;
		}
	};
}
#endif