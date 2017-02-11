#pragma once
#ifndef OPTTSP
#define OPTTSP
#include <algorithm>
#include <utility>
#include <vector>
#include <deque>
#include <list>
#include "Point.h"
#include "Basic.h"

using namespace std;

class Opttsp : public Basic{
private:
	unsigned int numPoints;
	double Ans;
	double tempAns;
	vector<vector<double>> dist;
	vector<unsigned int> ansVec;
	deque<unsigned int> unused;
	vector<unsigned int> curVec;
	const unsigned int expDe = 3;
public:
	Opttsp (ostream& inOut) : Basic(inOut){

	}
	inline bool promising();
	inline void judgeMax();
	inline void init();
	inline void work();
	inline double upperBound();
	inline double MSTBound();
	inline bool otherPromising(int );
	void help_work();
	~Opttsp(){};
};


inline void Opttsp::init() {
	cin >> numPoints;
	vector<Point> points(numPoints);
	dist.resize(numPoints);
	curVec.reserve(numPoints);

	for (unsigned int i = 0; i < numPoints; ++i) dist[i].resize(numPoints);
	for (unsigned int i = 0; i < numPoints; ++i)
		cin >> points[i].x >> points[i].y;

	for (unsigned int i = 0; i < numPoints; ++i) {
		for (unsigned int j = 0; j < i; ++j) {
			dist[j][i] = points[i].dis(points[j]);
			dist[i][j] = dist[j][i];
		}
	}

	for (unsigned int i = 1; i < numPoints; ++i) 
		unused.push_back(i);
}

inline void Opttsp::work() {
	Ans = this->upperBound();
	tempAns = 0;
	curVec.emplace_back(0);
	help_work();
	out << Ans << endl;
	for (unsigned int i = 0; i < ansVec.size(); ++i) out << ansVec[i] << " ";
	out << "\n";
}

inline void Opttsp::help_work() {
	if (unused.empty()) judgeMax();
	else if (unused.size() < expDe || promising()) {
		for (unsigned int i = 0; i < unused.size(); ++i) {
			if (otherPromising(unused.front())) {
				tempAns += dist[curVec.back()][unused.front()];
				curVec.push_back(unused.front());
				unused.pop_front();
				help_work();
				unused.push_back(curVec.back());
				curVec.pop_back();
				tempAns -= dist[curVec.back()][unused.back()];
			}
			else {
				unused.push_back(unused.front());
				unused.pop_front();
			}
		}
	}
	else;
}
inline bool Opttsp::otherPromising(int curPoint) {
	// require gen.size() > 3
	int size = curVec.size() - 1;
	int forSize = size - 1;
	for (int i = 1; i < forSize; ++i) {
		if (dist[curVec[i]][curVec[i - 1]] + dist[curVec[i]][curVec[i + 1]] - dist[curVec[i]][curPoint] - dist[curVec[i]][curVec[forSize]]
	> dist[curVec[size]][curVec[i - 1]] + dist[curVec[size]][curVec[i + 1]] - dist[curVec[size]][curPoint] - dist[curVec[size]][curVec[forSize]]) {
			return false;
		}
	}
	return true;
}

inline bool Opttsp::promising() {
	if (tempAns + MSTBound() > Ans) return false;
	return true;
}

inline void Opttsp::judgeMax() {
	double ansTry = tempAns + dist[0][curVec.back()];
	if (Ans > ansTry) {
		Ans = ansTry;
		ansVec.assign(curVec.begin(), curVec.end());
	}
}
inline double Opttsp::upperBound() {
	double tempDist = dist[0][1];
	double minDelta = 0, sum = 0;
	list<unsigned int> myList;

	myList.emplace_back(0);
	myList.emplace_back(1);
	myList.emplace_back(0);

	list<unsigned int>::iterator itBe = myList.begin();
	list<unsigned int>::iterator itAf = myList.begin()++;
	list<unsigned int>::iterator inPla = myList.begin();

	sum = tempDist * 2;

	for (unsigned int i = 2; i < numPoints; ++i) {
		minDelta = numeric_limits<double>::max();
		itBe = myList.begin();
		itAf = ++myList.begin();
		while (itAf != myList.end()) {	
			double tempDist = dist[i][*itAf] - dist[*itAf][*itBe] + dist[i][*itBe];
			if (minDelta >  tempDist) {
				minDelta = tempDist;
				inPla = itAf;
			}
			++itBe; ++itAf;
		}
		myList.insert(inPla, i);
		sum += minDelta;
	}
	myList.pop_back();
	ansVec.assign(myList.begin(), myList.end());
	return sum;
}

inline double Opttsp::MSTBound() {
	double minDist = numeric_limits<double>::max();
	double ans = numeric_limits<double>::max();
	vector<double> mstDist(unused.size(), numeric_limits<double>::max());
	vector<bool> inSet(unused.size(), false);
	unsigned int pos = 0;
	unsigned int oneEnd = curVec.back();
	double temp1 = numeric_limits<double>::max();
	unsigned int leftPoints = unused.size();
	mstDist[0] = 0;

	for (unsigned int x: unused) {
		ans = min(dist[0][x], ans);
		temp1 = min(dist[oneEnd][x] ,temp1);
	}

	ans += temp1;
	for (unsigned int i = 0; i < leftPoints; ++i) {

		minDist = numeric_limits<double>::max();
		for (unsigned int j = 0; j < leftPoints; ++j) {
			if (!inSet[j] && minDist > mstDist[j]) {
				minDist = mstDist[j];
				pos = j;
			}
		}

		ans += minDist;
		inSet[pos] = true;
		for (unsigned int j = 1; j < leftPoints; ++j) {
			if (!inSet[j]) 
				mstDist[j] = min(dist[unused[pos]][unused[j]], mstDist[j]);
		}
	}
	return ans;
}
#endif