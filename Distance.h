#pragma once
#include <cmath>
#include "Point.h"

class Distance
{
public:
	static double Euclidean(Point point1, Point point2) {
		double distance = 0.0;
		for (int i = 0; i < point1.size(); ++i) {
			distance += pow(point1[i] - point2[i], 2);
		}
		return sqrt(distance);
	}

	static double Manhatin(Point point1, Point point2) {
		double distance = 0.0;
		for (int i = 0; i < point1.size(); ++i) {
			distance += abs(point1[i] - point2[i]);
		}
		return distance;
	}
};

