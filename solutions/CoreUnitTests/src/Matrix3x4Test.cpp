#include "stdafx.h"

#include "../../../include/core/math/Matrix3x4.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace math;

namespace CoreUnitTests
{
	TEST_CLASS(Matrix3x4Test)
	{
	public:

		TEST_METHOD(Basic_Construction)
		{
			Matrix3x4 matrix;
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

			Matrix3x4 matrix2(3);
			Assert::AreEqual(matrix2.m[0], 3.0f);
			Assert::AreEqual(matrix2.m[1], 0.0f);
			Assert::AreEqual(matrix2.m[2], 0.0f);
			Assert::AreEqual(matrix2.m[3], 0.0f);
			Assert::AreEqual(matrix2.m[4], 0.0f);
			Assert::AreEqual(matrix2.m[5], 3.0f);
			Assert::AreEqual(matrix2.m[6], 0.0f);
			Assert::AreEqual(matrix2.m[7], 0.0f);
			Assert::AreEqual(matrix2.m[8], 0.0f);
			Assert::AreEqual(matrix2.m[9], 0.0f);
			Assert::AreEqual(matrix2.m[10], 3.0f);
			Assert::AreEqual(matrix2.m[11], 0.0f);

			Matrix3x4 matrix3(1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,
				7.0f,8.0f,9.0f,10.0f,11.0f,12.0f);
			Assert::AreEqual(matrix3.m[0], 1.0f);
			Assert::AreEqual(matrix3.m[1], 2.0f);
			Assert::AreEqual(matrix3.m[2], 3.0f);
			Assert::AreEqual(matrix3.m[3], 4.0f);
			Assert::AreEqual(matrix3.m[4], 5.0f);
			Assert::AreEqual(matrix3.m[5], 6.0f);
			Assert::AreEqual(matrix3.m[6], 7.0f);
			Assert::AreEqual(matrix3.m[7], 8.0f);
			Assert::AreEqual(matrix3.m[8], 9.0f);
			Assert::AreEqual(matrix3.m[9], 10.0f);
			Assert::AreEqual(matrix3.m[10], 11.0f);
			Assert::AreEqual(matrix3.m[11], 12.0f);
		}

		TEST_METHOD(Scalar_Multiplication)
		{
			Matrix3x4 matrix;
			Matrix3x4 result = matrix * 3;
			Assert::AreEqual(result.m[0], 3.0f);
			Assert::AreEqual(result.m[1], 0.0f);
			Assert::AreEqual(result.m[2], 0.0f);
			Assert::AreEqual(result.m[3], 0.0f);
			Assert::AreEqual(result.m[4], 0.0f);
			Assert::AreEqual(result.m[5], 3.0f);
			Assert::AreEqual(result.m[6], 0.0f);
			Assert::AreEqual(result.m[7], 0.0f);
			Assert::AreEqual(result.m[8], 0.0f);
			Assert::AreEqual(result.m[9], 0.0f);
			Assert::AreEqual(result.m[10], 3.0f);
			Assert::AreEqual(result.m[11], 0.0f);

			Matrix3x4 result2;
			result2 *= 3.0f;
			Assert::AreEqual(result2.m[0], 3.0f);
			Assert::AreEqual(result2.m[1], 0.0f);
			Assert::AreEqual(result2.m[2], 0.0f);
			Assert::AreEqual(result2.m[3], 0.0f);
			Assert::AreEqual(result2.m[4], .0f);
			Assert::AreEqual(result2.m[5], 3.0f);
			Assert::AreEqual(result2.m[6], 0.0f);
			Assert::AreEqual(result2.m[7], 0.0f);
			Assert::AreEqual(result2.m[8], 0.0f);
			Assert::AreEqual(result2.m[9], 0.0f);
			Assert::AreEqual(result2.m[10], 3.0f);
			Assert::AreEqual(result2.m[11], 0.0f);
		}

		TEST_METHOD(Multiplication_3x4X3x4)
		{
			Matrix3x4 matrix;
			matrix.m[0] = 1.0f;
			matrix.m[1] = 2.0f;
			matrix.m[2] = 3.0f;
			matrix.m[3] = 4.0f;
			matrix.m[4] = 5.0f;
			matrix.m[5] = 6.0f;
			matrix.m[6] = 7.0f;
			matrix.m[7] = 8.0f;
			matrix.m[8] = 9.0f;
			matrix.m[9] = 10.0f;
			matrix.m[10] = 11.0f;
			matrix.m[11] = 12.0f;

			Matrix3x4 matrix2;
			matrix2.m[0] = 11.0f;
			matrix2.m[1] = 12.0f;
			matrix2.m[2] = 31.0f;
			matrix2.m[3] = 44.0f;
			matrix2.m[4] = 51.0f;
			matrix2.m[5] = 69.0f;
			matrix2.m[6] = 73.0f;
			matrix2.m[7] = 82.0f;
			matrix2.m[8] = 99.0f;
			matrix2.m[9] = 17.0f;
			matrix2.m[10] = 8.0f;
			matrix2.m[11] = 21.0f;

			Matrix3x4 result = matrix * matrix2;
			Assert::AreEqual(result.m[0], 410.0f);
			Assert::AreEqual(result.m[1], 201.0f);
			Assert::AreEqual(result.m[2], 201.0f);
			Assert::AreEqual(result.m[3], 275.0f);
			Assert::AreEqual(result.m[4], 1054.0f);
			Assert::AreEqual(result.m[5], 593.0f);
			Assert::AreEqual(result.m[6], 649.0f);
			Assert::AreEqual(result.m[7], 867.0f);
			Assert::AreEqual(result.m[8], 1698.0f);
			Assert::AreEqual(result.m[9], 985.0f);
			Assert::AreEqual(result.m[10], 1097.0f);
			Assert::AreEqual(result.m[11], 1459.0f);

			Matrix3x4 result2 = matrix2 * matrix;
			Assert::AreEqual(result2.m[0], 350.0f);
			Assert::AreEqual(result2.m[1], 404.0f);
			Assert::AreEqual(result2.m[2], 458.0f);
			Assert::AreEqual(result2.m[3], 556.0f);
			Assert::AreEqual(result2.m[4], 1053.0f);
			Assert::AreEqual(result2.m[5], 1246.0f);
			Assert::AreEqual(result2.m[6], 1439.0f);
			Assert::AreEqual(result2.m[7], 1714.0f);
			Assert::AreEqual(result2.m[8], 256.0f);
			Assert::AreEqual(result2.m[9], 380.0f);
			Assert::AreEqual(result2.m[10], 504.0f);
			Assert::AreEqual(result2.m[11], 649.0f);

			Matrix3x4 result3 = matrix2;
			result3 *= matrix;
			Assert::AreEqual(result3.m[0], 350.0f);
			Assert::AreEqual(result3.m[1], 404.0f);
			Assert::AreEqual(result3.m[2], 458.0f);
			Assert::AreEqual(result3.m[3], 556.0f);
			Assert::AreEqual(result3.m[4], 1053.0f);
			Assert::AreEqual(result3.m[5], 1246.0f);
			Assert::AreEqual(result3.m[6], 1439.0f);
			Assert::AreEqual(result3.m[7], 1714.0f);
			Assert::AreEqual(result3.m[8], 256.0f);
			Assert::AreEqual(result3.m[9], 380.0f);
			Assert::AreEqual(result3.m[10], 504.0f);
			Assert::AreEqual(result3.m[11], 649.0f);
		}

		TEST_METHOD(Transform)
		{
			Matrix3x4 matrix;
			matrix.m[0] = 1.0f;
			matrix.m[1] = 2.0f;
			matrix.m[2] = 3.0f;
			matrix.m[3] = 4.0f;
			matrix.m[4] = 5.0f;
			matrix.m[5] = 6.0f;
			matrix.m[6] = 7.0f;
			matrix.m[7] = 8.0f;
			matrix.m[8] = 9.0f;
			matrix.m[9] = 10.0f;
			matrix.m[10] = 11.0f;
			matrix.m[11] = 12.0f;

			Vector3r vector(1.0f, -12.0f, 7.0f);
			Vector3r result = matrix.transform(vector);
			Assert::AreEqual(result.x, 2.0f);
			Assert::AreEqual(result.y, -10.0f);
			Assert::AreEqual(result.z, -22.0f);
		}

		TEST_METHOD(Determinant)
		{
			Matrix3x4 matrix;
			matrix.m[0] = 1.0f;
			matrix.m[1] = 2.0f;
			matrix.m[2] = 3.0f;
			matrix.m[3] = 4.0f;
			matrix.m[4] = 5.0f;
			matrix.m[5] = 6.0f;
			matrix.m[6] = 7.0f;
			matrix.m[7] = 8.0f;
			matrix.m[8] = 9.0f;
			matrix.m[9] = 10.0f;
			matrix.m[10] = 11.0f;
			matrix.m[11] = 12.0f;

			Real result = matrix.getDeterminant();
			Assert::AreEqual(result, 0.0f);

			Matrix3x4 matrix2;
			matrix2.m[0] = 11.0f;
			matrix2.m[1] = 12.0f;
			matrix2.m[2] = 31.0f;
			matrix2.m[3] = 7.0f;
			matrix2.m[4] = 44.0f;
			matrix2.m[5] = 51.0f;
			matrix2.m[6] = 69.0f;
			matrix2.m[7] = 15.0f;
			matrix2.m[8] = 73.0f;
			matrix2.m[9] = 82.0f;
			matrix2.m[10] = 99.0f;
			matrix2.m[11] = 21.0f;

			Real result2 = matrix2.getDeterminant();
			Assert::AreEqual(result2, -2092.0f);
		}

		TEST_METHOD(Inverse)
		{
			Matrix3x4 matrix;
			matrix.m[0] = 1.0f;
			matrix.m[1] = 2.0f;
			matrix.m[2] = 3.0f;
			matrix.m[3] = 55.0f;
			matrix.m[4] = 4.0f;
			matrix.m[5] = 5.0f;
			matrix.m[6] = 6.0f;
			matrix.m[7] = 19.0f;
			matrix.m[8] = 7.0f;
			matrix.m[9] = 8.0f;
			matrix.m[10] = 9.0f;
			matrix.m[11] = 105.0f;

			Matrix3x4 result = matrix.inverse();
			Assert::AreEqual(result.m[0], 1.0f);
			Assert::AreEqual(result.m[1], 0.0f);
			Assert::AreEqual(result.m[2], 0.0f);
			Assert::AreEqual(result.m[3], 0.0f);
			Assert::AreEqual(result.m[4], 0.0f);
			Assert::AreEqual(result.m[5], 1.0f);
			Assert::AreEqual(result.m[6], 0.0f);
			Assert::AreEqual(result.m[7], 0.0f);
			Assert::AreEqual(result.m[8], 0.0f);
			Assert::AreEqual(result.m[9], 0.0f);
			Assert::AreEqual(result.m[10], 1.0f);
			Assert::AreEqual(result.m[11], 0.0f);

			Matrix3x4 matrix2;
			matrix2.m[0] = 7.0;
			matrix2.m[1] = 2.0f;
			matrix2.m[2] = 1.0f;
			matrix2.m[3] = 23.0f;
			matrix2.m[4] = 0.0f;
			matrix2.m[5] = 3.0f;
			matrix2.m[6] = -1.0f;
			matrix2.m[7] = 115.0f;
			matrix2.m[8] = -3.0f;
			matrix2.m[9] = 4.0f;
			matrix2.m[10] = -2.0f;
			matrix2.m[11] = 62.0f;

			Matrix3x4 result2 = matrix2.inverse();
			Assert::AreEqual(result2.m[0], -2.0f);
			Assert::AreEqual(result2.m[1], 8.0f);
			Assert::AreEqual(result2.m[2], -5.0f);
			Assert::AreEqual(result2.m[3], -564.0f);
			Assert::AreEqual(result2.m[4], 3.0f);
			Assert::AreEqual(result2.m[5], -11.0f);
			Assert::AreEqual(result2.m[6], 7.0f);
			Assert::AreEqual(result2.m[7], -762.0f);
			Assert::AreEqual(result2.m[8], 9.0f);
			Assert::AreEqual(result2.m[9], -34.0f);
			Assert::AreEqual(result2.m[10], 21.0f);
			Assert::AreEqual(result2.m[11], 2401.0f);

			Matrix3x4 matrix3;
			matrix3.m[0] = 7.0;
			matrix3.m[1] = 2.0f;
			matrix3.m[2] = 1.0f;
			matrix3.m[3] = 23.0f;
			matrix3.m[4] = 0.0f;
			matrix3.m[5] = 3.0f;
			matrix3.m[6] = -1.0f;
			matrix3.m[7] = 115.0f;
			matrix3.m[8] = -3.0f;
			matrix3.m[9] = 4.0f;
			matrix3.m[10] = -2.0f;
			matrix3.m[11] = 62.0f;

			matrix3.invert();
			Assert::AreEqual(matrix3.m[0], -2.0f);
			Assert::AreEqual(matrix3.m[1], 8.0f);
			Assert::AreEqual(matrix3.m[2], -5.0f);
			Assert::AreEqual(matrix3.m[3], -564.0f);
			Assert::AreEqual(matrix3.m[4], 3.0f);
			Assert::AreEqual(matrix3.m[5], -11.0f);
			Assert::AreEqual(matrix3.m[6], 7.0f);
			Assert::AreEqual(matrix3.m[7], -762.0f);
			Assert::AreEqual(matrix3.m[8], 9.0f);
			Assert::AreEqual(matrix3.m[9], -34.0f);
			Assert::AreEqual(matrix3.m[10], 21.0f);
			Assert::AreEqual(matrix3.m[11], 2401.0f);
		}

		TEST_METHOD(SetOrientation_Quarternion)
		{
			//TODO
		}

		TEST_METHOD(Transform_inverse)
		{
			Matrix3x4 matrix;
			matrix.m[0] = 1.0f;
			matrix.m[1] = 2.0f;
			matrix.m[2] = 3.0f;
			matrix.m[3] = 4.0f;
			matrix.m[4] = 5.0f;
			matrix.m[5] = 6.0f;
			matrix.m[6] = 7.0f;
			matrix.m[7] = 8.0f;
			matrix.m[8] = 9.0f;
			matrix.m[9] = 10.0f;
			matrix.m[10] = 11.0f;
			matrix.m[11] = 12.0f;

			Vector3r translocate(1.0, -13.0f, 7.0f);
			Vector3r result = matrix.transformInverse(translocate);
			Assert::AreEqual(result.x, -153.0f);
			Assert::AreEqual(result.y, -182.0f);
			Assert::AreEqual(result.z, -211.0f);
		
		}

		TEST_METHOD(GetAxisValue)
		{
			Matrix3x4 matrix;
			matrix.m[0] = 1.0f;
			matrix.m[1] = 2.0f;
			matrix.m[2] = 3.0f;
			matrix.m[3] = 21.0f;
			matrix.m[4] = 4.0f;
			matrix.m[5] = 5.0f;
			matrix.m[6] = 6.0f;
			matrix.m[7] = 61.0f;
			matrix.m[8] = 7.0f;
			matrix.m[9] = 8.0f;
			matrix.m[10] = 9.0f;
			matrix.m[11] = 115.0f;

			Assert::AreEqual(matrix.getAxisValues(0).x, 1.0f);
			Assert::AreEqual(matrix.getAxisValues(0).y, 4.0f);
			Assert::AreEqual(matrix.getAxisValues(0).z, 7.0f);
			Assert::AreEqual(matrix.getAxisValues(1).x, 2.0f);
			Assert::AreEqual(matrix.getAxisValues(1).y, 5.0f);
			Assert::AreEqual(matrix.getAxisValues(1).z, 8.0f);
			Assert::AreEqual(matrix.getAxisValues(2).x, 3.0f);
			Assert::AreEqual(matrix.getAxisValues(2).y, 6.0f);
			Assert::AreEqual(matrix.getAxisValues(2).z, 9.0f);
		}
	};
}