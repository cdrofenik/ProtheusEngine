#include "stdafx.h"

#include "../../include/core/math/Matrix3.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PrometheusEngineUnitTests
{
	TEST_CLASS(Matrix3Test)
	{
	public:
		TEST_METHOD(Basic_Construction)
		{
			Matrix3 matrix;
			Assert::AreEqual(matrix.m[0], 1.0f);
			Assert::AreEqual(matrix.m[1], 0.0f);
			Assert::AreEqual(matrix.m[2], 0.0f);
			Assert::AreEqual(matrix.m[3], 0.0f);
			Assert::AreEqual(matrix.m[4], 1.0f);
			Assert::AreEqual(matrix.m[5], 0.0f);
			Assert::AreEqual(matrix.m[6], 0.0f);
			Assert::AreEqual(matrix.m[7], 0.0f);
			Assert::AreEqual(matrix.m[8], 1.0f);
		}

		TEST_METHOD(Scalar_Multiplication)
		{
			Matrix3 matrix;
			Matrix3 result = matrix * 3.0f;
			Assert::AreEqual(result.m[0], 3.0f);
			Assert::AreEqual(result.m[1], 0.0f);
			Assert::AreEqual(result.m[2], 0.0f);
			Assert::AreEqual(result.m[3], 0.0f);
			Assert::AreEqual(result.m[4], 3.0f);
			Assert::AreEqual(result.m[5], 0.0f);
			Assert::AreEqual(result.m[6], 0.0f);
			Assert::AreEqual(result.m[7], 0.0f);
			Assert::AreEqual(result.m[8], 3.0f);

			Matrix3 result2;
			result2 *= 3.0f;
			Assert::AreEqual(result2.m[0], 3.0f);
			Assert::AreEqual(result2.m[1], 0.0f);
			Assert::AreEqual(result2.m[2], 0.0f);
			Assert::AreEqual(result2.m[3], 0.0f);
			Assert::AreEqual(result2.m[4], 3.0f);
			Assert::AreEqual(result2.m[5], 0.0f);
			Assert::AreEqual(result2.m[6], 0.0f);
			Assert::AreEqual(result2.m[7], 0.0f);
			Assert::AreEqual(result2.m[8], 3.0f);
		}

		TEST_METHOD(Multiplication_3x3)
		{
			Matrix3 matrix;
			matrix.m[0] = 1.0f;
			matrix.m[1] = 2.0f;
			matrix.m[2] = 3.0f;
			matrix.m[3] = 4.0f;
			matrix.m[4] = 5.0f;
			matrix.m[5] = 6.0f;
			matrix.m[6] = 7.0f;
			matrix.m[7] = 8.0f;
			matrix.m[8] = 9.0f;

			Matrix3 matrix2;
			matrix2.m[0] = 11.0f;
			matrix2.m[1] = 12.0f;
			matrix2.m[2] = 31.0f;
			matrix2.m[3] = 44.0f;
			matrix2.m[4] = 51.0f;
			matrix2.m[5] = 69.0f;
			matrix2.m[6] = 73.0f;
			matrix2.m[7] = 82.0f;
			matrix2.m[8] = 99.0f;

			Matrix3 result = matrix * matrix2;
			Assert::AreEqual(result.m[0], 318.0f);
			Assert::AreEqual(result.m[1], 360.0f);
			Assert::AreEqual(result.m[2], 466.0f);
			Assert::AreEqual(result.m[3], 702.0f);
			Assert::AreEqual(result.m[4], 795.0f);
			Assert::AreEqual(result.m[5], 1063.0f);
			Assert::AreEqual(result.m[6], 1086.0f);
			Assert::AreEqual(result.m[7], 1230.0f);
			Assert::AreEqual(result.m[8], 1660.0f);

			Matrix3 result2 = matrix2 * matrix;
			Assert::AreEqual(result2.m[0], 276.0f);
			Assert::AreEqual(result2.m[1], 330.0f);
			Assert::AreEqual(result2.m[2], 384.0f);
			Assert::AreEqual(result2.m[3], 731.0f);
			Assert::AreEqual(result2.m[4], 895.0f);
			Assert::AreEqual(result2.m[5], 1059.0f);
			Assert::AreEqual(result2.m[6], 1094.0f);
			Assert::AreEqual(result2.m[7], 1348.0f);
			Assert::AreEqual(result2.m[8], 1602.0f);

			Matrix3 result3 = matrix2;
			result3 *= matrix;
			Assert::AreEqual(result2.m[0], 276.0f);
			Assert::AreEqual(result3.m[1], 330.0f);
			Assert::AreEqual(result3.m[2], 384.0f);
			Assert::AreEqual(result3.m[3], 731.0f);
			Assert::AreEqual(result3.m[4], 895.0f);
			Assert::AreEqual(result3.m[5], 1059.0f);
			Assert::AreEqual(result3.m[6], 1094.0f);
			Assert::AreEqual(result3.m[7], 1348.0f);
			Assert::AreEqual(result3.m[8], 1602.0f);
		}

		TEST_METHOD(Addition)
		{
			Matrix3 matrix;
			matrix.m[0] = 1.0f;
			matrix.m[1] = 2.0f;
			matrix.m[2] = 3.0f;
			matrix.m[3] = 4.0f;
			matrix.m[4] = 5.0f;
			matrix.m[5] = 6.0f;
			matrix.m[6] = 7.0f;
			matrix.m[7] = 8.0f;
			matrix.m[8] = 9.0f;

			Matrix3 matrix2;
			matrix2.m[0] = 11.0f;
			matrix2.m[1] = 12.0f;
			matrix2.m[2] = 31.0f;
			matrix2.m[3] = 44.0f;
			matrix2.m[4] = 51.0f;
			matrix2.m[5] = 69.0f;
			matrix2.m[6] = 73.0f;
			matrix2.m[7] = 82.0f;
			matrix2.m[8] = 99.0f;

			Matrix3 result = matrix + matrix2;
			Assert::AreEqual(result.m[0], 12.0f);
			Assert::AreEqual(result.m[1], 14.0f);
			Assert::AreEqual(result.m[2], 34.0f);
			Assert::AreEqual(result.m[3], 48.0f);
			Assert::AreEqual(result.m[4], 56.0f);
			Assert::AreEqual(result.m[5], 75.0f);
			Assert::AreEqual(result.m[6], 80.0f);
			Assert::AreEqual(result.m[7], 90.0f);
			Assert::AreEqual(result.m[8], 108.0f);

			Matrix3 result2 = matrix2 + matrix;
			Assert::AreEqual(result2.m[0], 12.0f);
			Assert::AreEqual(result2.m[1], 14.0f);
			Assert::AreEqual(result2.m[2], 34.0f);
			Assert::AreEqual(result2.m[3], 48.0f);
			Assert::AreEqual(result2.m[4], 56.0f);
			Assert::AreEqual(result2.m[5], 75.0f);
			Assert::AreEqual(result2.m[6], 80.0f);
			Assert::AreEqual(result2.m[7], 90.0f);
			Assert::AreEqual(result2.m[8], 108.0f);

			Matrix3 result3 = matrix2;
			result3 += matrix;
			Assert::AreEqual(result3.m[0], 12.0f);
			Assert::AreEqual(result3.m[1], 14.0f);
			Assert::AreEqual(result3.m[2], 34.0f);
			Assert::AreEqual(result3.m[3], 48.0f);
			Assert::AreEqual(result3.m[4], 56.0f);
			Assert::AreEqual(result3.m[5], 75.0f);
			Assert::AreEqual(result3.m[6], 80.0f);
			Assert::AreEqual(result3.m[7], 90.0f);
			Assert::AreEqual(result3.m[8], 108.0f);
		}

		TEST_METHOD(Vector3_Multiplication)
		{
			Matrix3 matrix;
			matrix.m[0] = 1.0f;
			matrix.m[1] = 2.0f;
			matrix.m[2] = 3.0f;
			matrix.m[3] = 4.0f;
			matrix.m[4] = 5.0f;
			matrix.m[5] = 6.0f;
			matrix.m[6] = 7.0f;
			matrix.m[7] = 8.0f;
			matrix.m[8] = 9.0f;

			Vector3r vector(1.0f, -12.0f, 7.0f);
			Vector3r result = matrix * vector;
			Assert::AreEqual(result.x, -2.0f);
			Assert::AreEqual(result.y, -14.0f);
			Assert::AreEqual(result.z, -26.0f);
		}

		TEST_METHOD(Transform)
		{
			Matrix3 matrix;
			matrix.m[0] = 1.0f;
			matrix.m[1] = 2.0f;
			matrix.m[2] = 3.0f;
			matrix.m[3] = 4.0f;
			matrix.m[4] = 5.0f;
			matrix.m[5] = 6.0f;
			matrix.m[6] = 7.0f;
			matrix.m[7] = 8.0f;
			matrix.m[8] = 9.0f;

			Vector3r vector(1.0f, -12.0f, 7.0f);
			Vector3r result = matrix.transform(vector);
			Assert::AreEqual(result.x, -2.0f);
			Assert::AreEqual(result.y, -14.0f);
			Assert::AreEqual(result.z, -26.0f);
		}

		TEST_METHOD(Determinant)
		{
			Matrix3 matrix;
			matrix.m[0] = 1.0f;
			matrix.m[1] = 2.0f;
			matrix.m[2] = 3.0f;
			matrix.m[3] = 4.0f;
			matrix.m[4] = 5.0f;
			matrix.m[5] = 6.0f;
			matrix.m[6] = 7.0f;
			matrix.m[7] = 8.0f;
			matrix.m[8] = 9.0f;

			Real result = matrix.getDeterminant();
			Assert::AreEqual(result, 0.0f);

			Matrix3 matrix2;
			matrix2.m[0] = 11.0f;
			matrix2.m[1] = 12.0f;
			matrix2.m[2] = 31.0f;
			matrix2.m[3] = 44.0f;
			matrix2.m[4] = 51.0f;
			matrix2.m[5] = 69.0f;
			matrix2.m[6] = 73.0f;
			matrix2.m[7] = 82.0f;
			matrix2.m[8] = 99.0f;

			Real result2 = matrix2.getDeterminant();
			Assert::AreEqual(result2, -2092.0f);
		}

		TEST_METHOD(Inverse)
		{
			Matrix3 matrix;
			matrix.m[0] = 1.0f;
			matrix.m[1] = 2.0f;
			matrix.m[2] = 3.0f;
			matrix.m[3] = 4.0f;
			matrix.m[4] = 5.0f;
			matrix.m[5] = 6.0f;
			matrix.m[6] = 7.0f;
			matrix.m[7] = 8.0f;
			matrix.m[8] = 9.0f;

			Matrix3 result = matrix.inverse();
			Assert::AreEqual(result.m[0], 1.0f);
			Assert::AreEqual(result.m[1], 0.0f);
			Assert::AreEqual(result.m[2], 0.0f);
			Assert::AreEqual(result.m[3], 0.0f);
			Assert::AreEqual(result.m[4], 1.0f);
			Assert::AreEqual(result.m[5], 0.0f);
			Assert::AreEqual(result.m[6], 0.0f);
			Assert::AreEqual(result.m[7], 0.0f);
			Assert::AreEqual(result.m[8], 1.0f);

			Matrix3 matrix2;
			matrix2.m[0] = 7.0;
			matrix2.m[1] = 2.0f;
			matrix2.m[2] = 1.0f;
			matrix2.m[3] = 0.0f;
			matrix2.m[4] = 3.0f;
			matrix2.m[5] = -1.0f;
			matrix2.m[6] = -3.0f;
			matrix2.m[7] = 4.0f;
			matrix2.m[8] = -2.0f;

			Matrix3 result2 = matrix2.inverse();
			Assert::AreEqual(result2.m[0], -2.0f);
			Assert::AreEqual(result2.m[1], 8.0f);
			Assert::AreEqual(result2.m[2], -5.0f);
			Assert::AreEqual(result2.m[3], 3.0f);
			Assert::AreEqual(result2.m[4], -11.0f);
			Assert::AreEqual(result2.m[5], 7.0f);
			Assert::AreEqual(result2.m[6], 9.0f);
			Assert::AreEqual(result2.m[7], -34.0f);
			Assert::AreEqual(result2.m[8], 21.0f);

			Matrix3 matrix3;
			matrix3.m[0] = 7.0;
			matrix3.m[1] = 2.0f;
			matrix3.m[2] = 1.0f;
			matrix3.m[3] = 0.0f;
			matrix3.m[4] = 3.0f;
			matrix3.m[5] = -1.0f;
			matrix3.m[6] = -3.0f;
			matrix3.m[7] = 4.0f;
			matrix3.m[8] = -2.0f;

			matrix3.invert();
			Assert::AreEqual(matrix3.m[0], -2.0f);
			Assert::AreEqual(matrix3.m[1], 8.0f);
			Assert::AreEqual(matrix3.m[2], -5.0f);
			Assert::AreEqual(matrix3.m[3], 3.0f);
			Assert::AreEqual(matrix3.m[4], -11.0f);
			Assert::AreEqual(matrix3.m[5], 7.0f);
			Assert::AreEqual(matrix3.m[6], 9.0f);
			Assert::AreEqual(matrix3.m[7], -34.0f);
			Assert::AreEqual(matrix3.m[8], 21.0f);
		}

		TEST_METHOD(Transpose)
		{
			Matrix3 matrix;
			matrix.m[0] = 1.0f;
			matrix.m[1] = 2.0f;
			matrix.m[2] = 3.0f;
			matrix.m[3] = 4.0f;
			matrix.m[4] = 5.0f;
			matrix.m[5] = 6.0f;
			matrix.m[6] = 7.0f;
			matrix.m[7] = 8.0f;
			matrix.m[8] = 9.0f;

			Matrix3 result = matrix.transpose();
			Assert::AreEqual(result.m[0], 1.0f);
			Assert::AreEqual(result.m[1], 4.0f);
			Assert::AreEqual(result.m[2], 7.0f);
			Assert::AreEqual(result.m[3], 2.0f);
			Assert::AreEqual(result.m[4], 5.0f);
			Assert::AreEqual(result.m[5], 8.0f);
			Assert::AreEqual(result.m[6], 3.0f);
			Assert::AreEqual(result.m[7], 6.0f);
			Assert::AreEqual(result.m[8], 9.0f);

			Assert::AreEqual(matrix.m[0], 1.0f);
			Assert::AreEqual(matrix.m[1], 2.0f);
			Assert::AreEqual(matrix.m[2], 3.0f);
			Assert::AreEqual(matrix.m[3], 4.0f);
			Assert::AreEqual(matrix.m[4], 5.0f);
			Assert::AreEqual(matrix.m[5], 6.0f);
			Assert::AreEqual(matrix.m[6], 7.0f);
			Assert::AreEqual(matrix.m[7], 8.0f);
			Assert::AreEqual(matrix.m[8], 9.0f);
		}

		TEST_METHOD(SetOrientation_Quarternion)
		{
			//TODO
		}
	};
}