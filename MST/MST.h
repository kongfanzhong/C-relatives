#pragma once
#ifndef MST
#define MST
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <sstream>
#include <iomanip>
#include <limits>
#include "Point.h"
#include "Basic.h"


using namespace std;
inline double getDist(Point& A, Point& B) {
	if (A.isWild()) {
		if (B.isBoOrWi()) return A.dis(B);
		else return numeric_limits<double>::max();
	}
	else if (B.isWild()) {
		if (A.isBorder()) return A.dis(B);
		else return numeric_limits<double>::max();
	}
	else
		return A.dis(B);
}

struct tracePoint {
	unsigned int prev;
	double val;
};

class Mst : public Basic {
private:
	unsigned int numPoints;
	vector<Point> points;
	vector<tracePoint> dist;
	vector<bool> inSet;
public:
	Mst(ostream& out):Basic(out) {}
	inline void init();
	inline void work();
	~Mst() {};
};


inline void Mst::init() {
	cin >> numPoints;
	points.resize(numPoints);
	dist.resize(numPoints);
	inSet.resize(numPoints);
	for (unsigned int i = 0; i < numPoints; ++i)
		cin >> points[i].x >> points[i].y;
}

inline void Mst::work() {
	double minDist = numeric_limits<double>::max();
	unsigned int pos;
	double ans = 0;
	for (unsigned int i = 1; i < numPoints; ++i) inSet[i] = false;
	inSet[0] = true;
	for (unsigned int i = 1; i < numPoints; ++i) dist[i].val = getDist(points[i], points[0]);
	
	for (unsigned int i = 1; i < numPoints; ++i) {

		minDist = numeric_limits<double>::max();
		for (unsigned int j = 0; j < numPoints; ++j) {
			if (!inSet[j] && minDist > dist[j].val) {
				minDist = dist[j].val;
				pos = j;
			}
		}

		if (minDist == numeric_limits<double>::max()) {
			cerr << "Cannot construct MST" << endl;
			exit(1);
		}

		ans += minDist;
		inSet[pos] = true;
		if (pos < dist[pos].prev) out << pos << " " << dist[pos].prev << endl;
		else out << dist[pos].prev << " " << pos << endl;

		for (unsigned int j = 0; j < numPoints; ++j) {
			if (!inSet[j]) {
				double tempDest = getDist(points[j], points[pos]);
				if (dist[j].val > tempDest) {
					dist[j].val = tempDest;
					dist[j].prev = pos;
				}
			}
		}
	}
	cout << ans << endl;
}



#endif