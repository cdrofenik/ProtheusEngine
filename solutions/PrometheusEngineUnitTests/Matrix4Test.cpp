#include "stdafx.h"

#include "../../include/core/math/Matrix4.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PrometheusEngineUnitTests
{
	TEST_CLASS(Matrix4Test)
	{
	public:
		TEST_METHOD(Basic_Construction)
		{
			Matrix4 matrix;
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

			Matrix3 matrix1;
			matrix1.m[0] = 1.0f;
			matrix1.m[1] = 2.0f;
			matrix1.m[2] = 3.0f;
			matrix1.m[3] = 4.0f;
			matrix1.m[4] = 5.0f;
			matrix1.m[5] = 6.0f;
			matrix1.m[6] = 7.0f;
			matrix1.m[7] = 8.0f;
			matrix1.m[8] = 9.0f;
			Matrix4 result(matrix1);
			Assert::AreEqual(result.m[0], 1.0f);
			Assert::AreEqual(result.m[1], 2.0f);
			Assert::AreEqual(result.m[2], 3.0f);
			Assert::AreEqual(result.m[3], 0.0f);
			Assert::AreEqual(result.m[4], 4.0f);
			Assert::AreEqual(result.m[5], 5.0f);
			Assert::AreEqual(result.m[6], 6.0f);
			Assert::AreEqual(result.m[7], 0.0f);
			Assert::AreEqual(result.m[8], 7.0f);
			Assert::AreEqual(result.m[9], 8.0f);
			Assert::AreEqual(result.m[10], 9.0f);
			Assert::AreEqual(result.m[11], 0.0f);
			Assert::AreEqual(result.m[12], 0.0f);
			Assert::AreEqual(result.m[13], 0.0f);
			Assert::AreEqual(result.m[14], 0.0f);
			Assert::AreEqual(result.m[15], 1.0f);

			Matrix3x4 matrix2;
			matrix2.m[0] = 1.0f;
			matrix2.m[1] = 2.0f;
			matrix2.m[2] = 3.0f;
			matrix2.m[3] = 55.0f;
			matrix2.m[4] = 4.0f;
			matrix2.m[5] = 5.0f;
			matrix2.m[6] = 6.0f;
			matrix2.m[7] = 19.0f;
			matrix2.m[8] = 7.0f;
			matrix2.m[9] = 8.0f;
			matrix2.m[10] = 9.0f;
			matrix2.m[11] = 105.0f;
			Matrix4 result2(matrix2);
			Assert::AreEqual(result2.m[0], 1.0f);
			Assert::AreEqual(result2.m[1], 2.0f);
			Assert::AreEqual(result2.m[2], 3.0f);
			Assert::AreEqual(result2.m[3], 55.0f);
			Assert::AreEqual(result2.m[4], 4.0f);
			Assert::AreEqual(result2.m[5], 5.0f);
			Assert::AreEqual(result2.m[6], 6.0f);
			Assert::AreEqual(result2.m[7], 19.0f);
			Assert::AreEqual(result2.m[8], 7.0f);
			Assert::AreEqual(result2.m[9], 8.0f);
			Assert::AreEqual(result2.m[10], 9.0f);
			Assert::AreEqual(result2.m[11], 105.0f);
			Assert::AreEqual(result2.m[12], 0.0f);
			Assert::AreEqual(result2.m[13], 0.0f);
			Assert::AreEqual(result2.m[14], 0.0f);
			Assert::AreEqual(result2.m[15], 1.0f);

			Matrix4 result4(1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,
				8.0f,9.0f,10.0f,11.0f,12.0f,13.0f,14.0f,15.0f, 16.0f);
			Assert::AreEqual(result4.m[0], 1.0f);
			Assert::AreEqual(result4.m[1], 2.0f);
			Assert::AreEqual(result4.m[2], 3.0f);
			Assert::AreEqual(result4.m[3], 4.0f);
			Assert::AreEqual(result4.m[4], 5.0f);
			Assert::AreEqual(result4.m[5], 6.0f);
			Assert::AreEqual(result4.m[6], 7.0f);
			Assert::AreEqual(result4.m[7], 8.0f);
			Assert::AreEqual(result4.m[8], 9.0f);
			Assert::AreEqual(result4.m[9], 10.0f);
			Assert::AreEqual(result4.m[10], 11.0f);
			Assert::AreEqual(result4.m[11], 12.0f);
			Assert::AreEqual(result4.m[12], 13.0f);
			Assert::AreEqual(result4.m[13], 14.0f);
			Assert::AreEqual(result4.m[14], 15.0f);
			Assert::AreEqual(result4.m[15], 16.0f);
		}

		TEST_METHOD(Multiplication_4x4)
		{
			Matrix4 matrix(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
				8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
			
			Matrix4 result = matrix * matrix;
			Assert::AreEqual(result.m[0], 90.0f);
			Assert::AreEqual(result.m[1], 100.0f);
			Assert::AreEqual(result.m[2], 110.0f);
			Assert::AreEqual(result.m[3], 120.0f);
			Assert::AreEqual(result.m[4], 202.0f);
			Assert::AreEqual(result.m[5], 228.0f);
			Assert::AreEqual(result.m[6], 254.0f);
			Assert::AreEqual(result.m[7], 280.0f);
			Assert::AreEqual(result.m[8], 314.0f);
			Assert::AreEqual(result.m[9], 356.0f);
			Assert::AreEqual(result.m[10], 398.0f);
			Assert::AreEqual(result.m[11], 440.0f);
			Assert::AreEqual(result.m[12], 426.0f);
			Assert::AreEqual(result.m[13], 484.0f);
			Assert::AreEqual(result.m[14], 542.0f);
			Assert::AreEqual(result.m[15], 600.0f);
		}

		TEST_METHOD(Addition)
		{
			Matrix4 matrix(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
				8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

			Matrix4 result = matrix + matrix;
			Assert::AreEqual(result.m[0], 2.0f);
			Assert::AreEqual(result.m[1], 4.0f);
			Assert::AreEqual(result.m[2], 6.0f);
			Assert::AreEqual(result.m[3], 8.0f);
			Assert::AreEqual(result.m[4], 10.0f);
			Assert::AreEqual(result.m[5], 12.0f);
			Assert::AreEqual(result.m[6], 14.0f);
			Assert::AreEqual(result.m[7], 16.0f);
			Assert::AreEqual(result.m[8], 18.0f);
			Assert::AreEqual(result.m[9], 20.0f);
			Assert::AreEqual(result.m[10], 22.0f);
			Assert::AreEqual(result.m[11], 24.0f);
			Assert::AreEqual(result.m[12], 26.0f);
			Assert::AreEqual(result.m[13], 28.0f);
			Assert::AreEqual(result.m[14], 30.0f);
			Assert::AreEqual(result.m[15], 32.0f);
		}

		TEST_METHOD(Transpose)
		{
			Matrix4 matrix(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f,
				8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

			Matrix4 result = matrix.transpose();
			Assert::AreEqual(result.m[0], 1.0f);
			Assert::AreEqual(result.m[1], 5.0f);
			Assert::AreEqual(result.m[2], 9.0f);
			Assert::AreEqual(result.m[3], 13.0f);
			Assert::AreEqual(result.m[4], 2.0f);
			Assert::AreEqual(result.m[5], 6.0f);
			Assert::AreEqual(result.m[6], 10.0f);
			Assert::AreEqual(result.m[7], 14.0f);
			Assert::AreEqual(result.m[8], 3.0f);
			Assert::AreEqual(result.m[9], 7.0f);
			Assert::AreEqual(result.m[10], 11.0f);
			Assert::AreEqual(result.m[11], 15.0f);
			Assert::AreEqual(result.m[12], 4.0f);
			Assert::AreEqual(result.m[13], 8.0f);
			Assert::AreEqual(result.m[14], 12.0f);
			Assert::AreEqual(result.m[15], 16.0f);
		}
	};
}