#ifndef PROMETHEUS_TRANSFORM_HPP
#define PROMETHEUS_TRANSFORM_HPP

#include "ProVector3.hpp"
#include "ProMatrix4.hpp"

namespace NeptunePhysics {
	
	class ProTransform
	{
	public:
		ProTransform() { m_scale = ProVector3r(1.0f, 1.0f, 1.0f); m_origin = ProVector3r(0.0f, 0.0f, 0.0f); m_translation = ProVector3r(0.0f, 0.0f, 0.0f); }
		~ProTransform() { }

		void setScale(const ProReal& _x, const ProReal& _y, const ProReal& _z)  { m_scale = ProVector3r(_x, _y, _z); m_wasChanged = true; }
		void setOrigin(const ProReal& _x, const ProReal& _y, const ProReal& _z) { m_origin = ProVector3r(_x, _y, _z); m_wasChanged = true; }
		void setRotation(const ProReal& _alfaX, const ProReal& _alfaY, const ProReal& _alfaZ) { m_rotation = ProVector3r(_alfaX, _alfaY, _alfaZ); m_wasChanged = true; }
		void setTranslation(const ProReal& _x, const ProReal& _y, const ProReal& _z) { m_translation = ProVector3r(_x, _y, _z); m_wasChanged = true; }

		/*
		Returns Model matrix which can be manipulated through setScale, setOrigin and setRotation
		*/
		const ProMatrix4 getTransformMatrix() {
			if (m_wasChanged) {
				m_finalTransformation = getTranslationMatrix() * getRotationMatrix() * getScaleMatrix();
				m_wasChanged = false;
			}
			
			return m_finalTransformation;
		}

	private:
		bool m_wasChanged = false;
		ProVector3r m_scale;
		ProVector3r m_rotation;
		ProVector3r m_origin;
		ProVector3r m_translation;
		ProMatrix4 m_finalTransformation;

		ProMatrix4 getTranslationMatrix() {
			ProMatrix4 v;
			v.m[0] = 1.0f;	v.m[1] = 0.0f;	v.m[2] = 0.0f;	v.m[3] = m_origin.x + m_translation.x;
			v.m[4] = 0.0f;	v.m[5] = 1.0f;	v.m[6] = 0.0f;	v.m[7] = m_origin.y + m_translation.y;
			v.m[8] = 0.0f;	v.m[9] = 0.0f;	v.m[10] = 1.0f;	v.m[11] = m_origin.z + m_translation.z;
			v.m[12] = 0.0f;	v.m[13] = 0.0f;	v.m[14] = 0.0f;	v.m[15] = 1.0f;

			return v;
		}

		ProMatrix4 getScaleMatrix() {
			ProMatrix4 v;
			v.m[0] = m_scale.x;	v.m[1] = 0.0f;		v.m[2] = 0.0f;		v.m[3] = 0.0f;
			v.m[4] = 0.0f;		v.m[5] = m_scale.y;	v.m[6] = 0.0f;		v.m[7] = 0.0f;
			v.m[8] = 0.0f;		v.m[9] = 0.0f;		v.m[10] = m_scale.z;	v.m[11] = 0.0f;
			v.m[12] = 0.0f;		v.m[13] = 0.0f;		v.m[14] = 0.0f;		v.m[15] = 1.0f;
			return v;
		}

		ProMatrix4 getRotationMatrix() {
			ProMatrix4 v;

			//Rotation around z
			ProMatrix4 aroundZ;
			aroundZ.m[0] = cosf(m_rotation.z);	aroundZ.m[1] = -sinf(m_rotation.z);	aroundZ.m[2] = 0.0f;	aroundZ.m[3] = 0.0f;
			aroundZ.m[4] = sinf(m_rotation.z);	aroundZ.m[5] = cosf(m_rotation.z);	aroundZ.m[6] = 0.0f;	aroundZ.m[7] = 0.0f;
			aroundZ.m[8] = 0.0f;				aroundZ.m[9] = 0.0f;				aroundZ.m[10] = 1.0f;	aroundZ.m[11] = 0.0f;
			aroundZ.m[12] = 0.0f;				aroundZ.m[13] = 0.0f;				aroundZ.m[14] = 0.0f;	aroundZ.m[15] = 1.0f;

			//Rotation around y
			ProMatrix4 aroundY;
			aroundY.m[0] = cosf(m_rotation.y);	aroundY.m[1] = 0.0f;	aroundY.m[2] = -sinf(m_rotation.y);	aroundY.m[3] = 0.0f;
			aroundY.m[4] = 0.0f;				aroundY.m[5] = 1.0f;	aroundY.m[6] = 0.0f;				aroundY.m[7] = 0.0f;
			aroundY.m[8] = sinf(m_rotation.y);	aroundY.m[9] = 0.0f;	aroundY.m[10] = cosf(m_rotation.y);	aroundY.m[11] = 0.0f;
			aroundY.m[12] = 0.0f;				aroundY.m[13] = 0.0f;	aroundY.m[14] = 0.0f;				aroundY.m[15] = 1.0f;

			//Rotation around x
			ProMatrix4 aroundX;
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