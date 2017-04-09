#ifndef PROMETHEUS_VECTOR2_HPP
#define PROMETHEUS_VECTOR2_HPP

#include "ProPrecision.hpp"

template <typename T>
class ProVector2 {
public:
	T x, y;
	npVector2() : x(0), y(0) {}
	npVector2(T xx, T yy) : x(xx), y(yy) {}
};

typedef ProVector2<float> ProVector2f;
typedef ProVector2<int> ProVector2i;

#endif