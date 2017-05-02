#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include "Precision.hpp"

namespace math {

	template <typename T>
	class Vector2 {
	public:
		T x, y;
		Vector2() : x(0), y(0) {}
		Vector2(const T& xx, const T& yy) : x(xx), y(yy) {}
	};

	typedef Vector2<Real> Vector2r;
	typedef Vector2<int> Vector2i;
}

#endif