#include "stdafx.h"

#include "../../include/core/collections/AlignedArray.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace collections;

namespace PrometheusEngineUnitTests
{
	bool compare(int a, int b)
	{
		if (a < b)
			return true;
		else
			return false;
	}

	TEST_CLASS(AlignedArrayTest)
	{
	public:
		TEST_METHOD(Basic_Construction)
		{
			AlignedArray<int> a;

			Assert::AreEqual(a.size(), 0);
			Assert::AreEqual(a.capacity(), 0);

			a.reserve(20);

			Assert::AreEqual(a.size(), 0);
			Assert::AreEqual(a.capacity(), 20);
		}

		TEST_METHOD(Fill_And_Fetch_Data) {

			AlignedArray<int> a;
			a.reserve(20);

			for (int i = 0; i < 20; i++)
			{
				a.push_back(i);
			}


			for (int i = 0; i < 20; i++)
			{
				Assert::AreEqual(a[i], i);
				Assert::AreEqual(a.at(i), i);
			}
		}

		

		TEST_METHOD(Fill_And_Sort) {

			AlignedArray<int> a;
			a.reserve(20);

			for (int i = 0; i < 20; i++)
			{
				int value = i % 3 ? i * (-1) : i * 2;
				a.push_back(value);
			}

			a.bubbleSort(compare);
			for (int i = 1; i < 19; i++)
			{
				bool result = a[i] > a[i - 1];
				Assert::IsTrue(result);
			}
		}

		TEST_METHOD(Changed_values_with_pointer) {

			struct testStruct
			{
				testStruct(int val) : value(val) {}
				int value;
			};

			AlignedArray<testStruct> a;
			a.reserve(20);

			for (int i = 0; i < 20; i++)
			{
				int value = i;
				testStruct ts = testStruct(value);
				a.push_back(ts);
			}

			testStruct* ref =& a.at(19);
			ref->value = 21;

			for (int i = 1; i < 18; i++)
			{
				Assert::AreEqual(a[i].value, i);
			}
			Assert::AreEqual(a[19].value, 21);
		}
	};
}