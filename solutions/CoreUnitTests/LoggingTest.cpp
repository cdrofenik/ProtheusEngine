#include "stdafx.h"

#include "../../include/core/math/Vector3.hpp"
#include "../../include/core/math/Matrix3.hpp"
#include "../../include/core/logging/DebugUtils.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace logging;
using namespace math;

namespace PrometheusEngineUnitTests
{
	TEST_CLASS(AlignedArrayTest)
	{
	public:
		TEST_METHOD(LoggingTest)
		{

		//Log_DEBUG("LoggingTest", "char value", "test");

		//Log_DEBUG("LoggingTest", "integer value", 5);

		//Log_DEBUG("LoggingTest", "float value", 4.3f);

			Vector3r b(1.0f, 2.0f, 3.0f);
			DebugUtils::LOG_DEBUG("LoggingTest", "npVector3 b", b);

			Matrix3 a;
			DebugUtils::LOG_DEBUG("LoggingTest", "npMatrix3 a", a);
		}
	};
}