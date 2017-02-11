#pragma once
#ifndef BASIC
#define	BASIC
#include <iostream>
using namespace std;

class Basic {
public:
	ostream & out;
	Basic(ostream& inOut);
	virtual inline void init() = 0;
	virtual inline void work() = 0;
	virtual ~Basic() = 0;
};

Basic::Basic(ostream& inOut):out(inOut){
	
}


#endif