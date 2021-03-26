#pragma once
#include "PathPoint.h"

struct point_and_cost {
	int cost;
	PathPoint * point;
	point_and_cost(int i_cost, PathPoint * i_point) {
		cost = i_cost;
		point = i_point;
	}
};

inline bool operator>(const point_and_cost& pair1, const point_and_cost& pair2) {
	return pair1.cost > pair2.cost;
}
