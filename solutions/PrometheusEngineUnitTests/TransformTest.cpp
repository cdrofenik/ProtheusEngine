#include "stdafx.h"

#include "../../include/core/math/Transform.hpp"

#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PrometheusEngineUnitTests
{
	TEST_CLASS(TransformTest)
	{
	public:
		TEST_METHOD(Basic_Construction)
		{
			Transform transform;
			Matrix4 matrix = transform.getTransformMatrix();
			Assert::AreEqual(matrix.m[0], 1.0f);
			Assert::AreEqual(matrix.m[1], 0.0f);
			Assert::AreEqual(matrix.m[2], 0.0f);
			Assert::AreEqual(matrix.m[3], 0.0f);
			Assert::AreEqual(matrix.m[4], 0.0f);
			Assert::AreEqual(matrix.m[5], 1.0f);
			Assert::AreEqual(matrix.m[6], 0.0f);
			Assert::AreEqual(matrix.m[7], 0.0f);
			Assert::AreEqual(matrix.m[8], 0.0f);
			Assert::AreEqual(matrix.m[9], 0.0f);
			Assert::AreEqual(matrix.m[10], 1.0f);
			Assert::AreEqual(matrix.m[11], 0.0f);
			Assert::AreEqual(matrix.m[12], 0.0f);
			Assert::AreEqual(matrix.m[13], 0.0f);
			Assert::AreEqual(matrix.m[14], 0.0f);
			Assert::AreEqual(matrix.m[15], 1.0f);
		}

		TEST_METHOD(Origin)
		{
			Transform transform;
			transform.setOrigin(3.0f, 3.0f, 2.5f);
			Matrix4 matrix = transform.getTransformMatrix();
			Assert::AreEqual(matrix.m[0], 1.0f);
			Assert::AreEqual(matrix.m[1], 0.0f);
			Assert::AreEqual(matrix.m[2], 0.0f);
			Assert::AreEqual(matrix.m[3], 3.0f);
			Assert::AreEqual(matrix.m[4], 0.0f);
			Assert::AreEqual(matrix.m[5], 1.0f);
			Assert::AreEqual(matrix.m[6], 0.0f);
			Assert::AreEqual(matrix.m[7], 3.0f);
			Assert::AreEqual(matrix.m[8], 0.0f);
			Assert::AreEqual(matrix.m[9], 0.0f);
			Assert::AreEqual(matrix.m[10], 1.0f);
			Assert::AreEqual(matrix.m[11], 2.50f);
			Assert::AreEqual(matrix.m[12], 0.0f);
			Assert::AreEqual(matrix.m[13], 0.0f);
			Assert::AreEqual(matrix.m[14], 0.0f);
			Assert::AreEqual(matrix.m[15], 1.0f);
		}

		TEST_METHOD(Translation)
		{
			Transform transform;
			transform.setTranslation(3.0f, 3.0f, 2.5f);
			Matrix4 matrix = transform.getTransformMatrix();
			Assert::AreEqual(matrix.m[0], 1.0f);
			Assert::AreEqual(matrix.m[1], 0.0f);
			Assert::AreEqual(matrix.m[2], 0.0f);
			Assert::AreEqual(matrix.m[3], 3.0f);
			Assert::AreEqual(matrix.m[4], 0.0f);
			Assert::AreEqual(matrix.m[5], 1.0f);
			Assert::AreEqual(matrix.m[6], 0.0f);
			Assert::AreEqual(matrix.m[7], 3.0f);
			Assert::AreEqual(matrix.m[8], 0.0f);
			Assert::AreEqual(matrix.m[9], 0.0f);
			Assert::AreEqual(matrix.m[10], 1.0f);
			Assert::AreEqual(matrix.m[11], 2.50f);
			Assert::AreEqual(matrix.m[12], 0.0f);
			Assert::AreEqual(matrix.m[13], 0.0f);
			Assert::AreEqual(matrix.m[14], 0.0f);
			Assert::AreEqual(matrix.m[15], 1.0f);
		}

		TEST_METHOD(Scale)
		{
			Transform transform;
			transform.setScale(3.0f, 3.0f, 2.5f);
			Matrix4 matrix = transform.getTransformMatrix();
			Assert::AreEqual(matrix.m[0], 3.0f);
			Assert::AreEqual(matrix.m[1], 0.0f);
			Assert::AreEqual(matrix.m[2], 0.0f);
			Assert::AreEqual(matrix.m[3], 0.0f);
			Assert::AreEqual(matrix.m[4], 0.0f);
			Assert::AreEqual(matrix.m[5], 3.0f);
			Assert::AreEqual(matrix.m[6], 0.0f);
			Assert::AreEqual(matrix.m[7], 0.0f);
			Assert::AreEqual(matrix.m[8], 0.0f);
			Assert::AreEqual(matrix.m[9], 0.0f);
			Assert::AreEqual(matrix.m[10], 2.5f);
			Assert::AreEqual(matrix.m[11], 0.0f);
			Assert::AreEqual(matrix.m[12], 0.0f);
			Assert::AreEqual(matrix.m[13], 0.0f);
			Assert::AreEqual(matrix.m[14], 0.0f);
			Assert::AreEqual(matrix.m[15], 1.0f);
		}

		TEST_METHOD(Rotation)
		{
			Transform transform;
			Real value = sin(0.5);
			transform.setRotation(value * 0.1, value * 2, value * 10);
			Matrix4 matrix = transform.getTransformMatrix();
			Assert::AreEqual(matrix.m[0], 0.0469765f, 0.000001f);
			Assert::AreEqual(matrix.m[1], 0.998713f, 0.000001f);
			Assert::AreEqual(matrix.m[2], -0.0190947f, 0.000001f);
			Assert::AreEqual(matrix.m[3], 0.0f, 0.000001f);
			Assert::AreEqual(matrix.m[4], -0.572537f, 0.000001f);
			Assert::AreEqual(matrix.m[5], 0.0425848f, 0.000001f);
			Assert::AreEqual(matrix.m[6], 0.818722f, 0.0001f);
			Assert::AreEqual(matrix.m[7], 0.0f, 0.000001f);
			Assert::AreEqual(matrix.m[8], 0.818532f, 0.000001f);
			Assert::AreEqual(matrix.m[9], -0.0275306f, 0.000001f);
			Assert::AreEqual(matrix.m[10], 0.573801f, 0.000001f);
			Assert::AreEqual(matrix.m[11], 0.0f, 0.000001f);
			Assert::AreEqual(matrix.m[12], 0.0f, 0.000001f);
			Assert::AreEqual(matrix.m[13], 0.0f, 0.000001f);
			Assert::AreEqual(matrix.m[14], 0.0f, 0.000001f);
			Assert::AreEqual(matrix.m[15], 1.0f, 0.000001f);
		}

		TEST_METHOD(TransformMatrix)
		{
			Transform transform;
			transform.setTranslation(3.0f, 1.0f, 2.5f);
			Real value = sin(0.5);
			transform.setRotation(0.0f, value * 2, 0.0f);
			transform.setScale(2.0f, 7.0f, 5.0f);
			Matrix4 matrix = transform.getTransformMatrix();
			Assert::AreEqual(matrix.m[0], 1.14892f, 0.00001f);
			Assert::AreEqual(matrix.m[1], 0.0f);
			Assert::AreEqual(matrix.m[2], -4.09266f, 0.00001f);
			Assert::AreEqual(matrix.m[3], 3.0f);
			Assert::AreEqual(matrix.m[4], 0.0f);
			Assert::AreEqual(matrix.m[5], 7.0f);
			Assert::AreEqual(matrix.m[6], 0.0f);
			Assert::AreEqual(matrix.m[7], 1.0f);
			Assert::AreEqual(matrix.m[8], 1.63706f, 0.00001f);
			Assert::AreEqual(matrix.m[9], 0.0f);
			Assert::AreEqual(matrix.m[10], 2.8723f, 0.00001f);
			Assert::AreEqual(matrix.m[11], 2.50f);
			Assert::AreEqual(matrix.m[12], 0.0f);
			Assert::AreEqual(matrix.m[13], 0.0f);
			Assert::AreEqual(matrix.m[14], 0.0f);
			Assert::AreEqual(matrix.m[15], 1.0f);
		}

		TEST_METHOD(ProjectionMatrix)
		{
			Transform transform;
			Matrix4 matrix =
				transform.projectionMatrix(45.0f, 1024.0f / 768.0f, 0.1f, 100.0f);
			Assert::AreEqual(matrix.m[0], 1.3443320f, 0.001f); //Be careful
			Assert::AreEqual(matrix.m[1], 0.0f);
			Assert::AreEqual(matrix.m[2], 0.0f);
			Assert::AreEqual(matrix.m[3], 0.0f);
			Assert::AreEqual(matrix.m[4], 0.0f);
			Assert::AreEqual(matrix.m[5], 1.79259098f, 0.000001f);
			Assert::AreEqual(matrix.m[6], 0.0f);
			Assert::AreEqual(matrix.m[7], 0.0f);
			Assert::AreEqual(matrix.m[8], 0.0f);
			Assert::AreEqual(matrix.m[9], 0.0f);
			Assert::AreEqual(matrix.m[10], -1.00200200f, 0.000001f);
			Assert::AreEqual(matrix.m[11], -0.200200200f, 0.000001f);
			Assert::AreEqual(matrix.m[12], 0.0f);
			Assert::AreEqual(matrix.m[13], 0.0f);
			Assert::AreEqual(matrix.m[14], -1.0f, 0.000001f);
			Assert::AreEqual(matrix.m[15], 0.0f);
		}
	};
}