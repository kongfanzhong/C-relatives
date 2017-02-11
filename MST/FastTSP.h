#pragma once
#ifndef FASTTSP
#define FASTTSP
#include "Basic.h"
#include "Point.h"
#include <vector>
#include <list>
using namespace std;

class FastTSP : public Basic {
private:
	unsigned int numPoints;
	vector<Point> points;
	list<unsigned int> myList;
public:
	FastTSP(ostream& inOut) : Basic(inOut){

	}
	inline void init();
	inline void work();
	~FastTSP() {};
};

inline void FastTSP::init() {
	cin >> numPoints;
	points.resize(numPoints);
	for (unsigned int i = 0; i < numPoints; ++i)
		cin >> points[i].x >> points[i].y;
}

inline void FastTSP::work() {
	double tempDist = points[0].dis(points[1]);
	double minDelta = 0, sum = 0;
	unsigned int tempNode;
	tempNode = 0;
	myList.push_back(tempNode);
	tempNode = 1;
	myList.push_back(tempNode);
	tempNode = 0;
	myList.push_back(tempNode);
	
	list<unsigned int>::iterator itBe = myList.begin();
	list<unsigned int>::iterator itAf = myList.begin() ++;
	list<unsigned int>::iterator inPla = myList.begin();

	sum = tempDist * 2;

	for (unsigned int i = 2; i < numPoints; ++i) {
		minDelta = numeric_limits<double>::max();
		itBe = myList.begin();
		itAf = ++myList.begin();
		while (itAf != myList.end()) {
			double tempDist = points[i].dis(points[*itAf]) - points[*itBe].dis(points[*itAf]) + points[i].dis(points[*itBe]);
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
	cout << sum << endl;
	for (auto x : myList) {
		cout << x << " ";
	}
	cout << "\n";
}
#endif