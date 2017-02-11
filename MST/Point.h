#pragma once
#ifndef POINT
#define POINT
#include <math.h>
struct Point {
	int x, y;
	inline bool isWild() {
		return ((x < 0) && (y < 0));
	}
	inline bool isBorder() {
		return ( (x == 0) && (y <= 0) )  || ( (y == 0) && (x <= 0) );
	}
	inline bool isBoOrWi() {
		return ((x <= 0) && (y <= 0));
	}
	inline double dis(Point& A) {
		return sqrt( (long long) (x - A.x) * (x - A.x) + (long long) (y - A.y) * (y - A.y) );
	}
};


#endif // POINT