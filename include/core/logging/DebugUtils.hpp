#ifndef DEBUG_UTILS_H
#define DEBUG_UTILS_H

#include "../math/Precision.hpp"
#include "../math/Vector2.hpp"
#include "../math/Vector3.hpp"
#include "../math/Matrix4.hpp"

#include <iostream>

namespace logging {

	class DebugUtils {
	public:
		static void LOG_DEBUG(const char* location, const char* message, const math::Vector2r& value) {
			printf("DEBUG: [%s] %s: (%f, %f) \n", location, message, value.x, value.y);
		}

		static void LOG_DEBUG(const char* location, const char* message, const math::Vector3r& value) {
			printf("DEBUG: [%s] %s: (%f, %f, %f) \n", location, message, value.x, value.y, value.z);
		}

		static void LOG_DEBUG(const char* location, const char* message, const math::Matrix3& value) {
			printf("DEBUG: [%s] %s:\n(%f, %f, %f)\n(%f, %f, %f)\n(%f, %f, %f)\n", location, message, value.m[0], value.m[1], value.m[2],
				value.m[3], value.m[3], value.m[4], value.m[5], value.m[7], value.m[8]);
		}

		static void LOG_DEBUG(const char* location, const char* message, const math::Matrix4& value) {
			printf("DEBUG: [%s] %s:\n(%f, %f, %f, %f)\n(%f, %f, %f, %f)\n(%f, %f, %f, %f)\n(%f, %f, %f, %f)\n", location, message,
				value.m[0], value.m[1], value.m[2], value.m[3],
				value.m[4], value.m[5], value.m[6], value.m[7],
				value.m[8], value.m[9], value.m[10], value.m[11],
				value.m[12], value.m[13], value.m[14], value.m[15]);
		}
	};
}
#endif
