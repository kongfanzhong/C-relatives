/*
simple MST problems...
*/

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <sstream>
#include <iomanip>
#include <getopt.h>
#include "Basic.h"
#include "MST.h"
#include "Point.h"
#include "FastTSP.h"
#include "Opttsp.h"
using namespace std;


inline void getMode(int argc, char * argv[], Basic* & basic, ostream& out) {
	bool modeSpecified = false;
	string mode;
	int choice, option_index = 0;
	option long_options[] = {
		{"help",	no_argument,	nullptr,	'h'},
		{"mode",	required_argument,	nullptr,'m'},
		{ nullptr, 0,                 nullptr, '\0' }
	};

	while ((choice = getopt_long(argc, argv, "hm:", long_options, &option_index)) != -1) {
		switch (choice) {
		case 'h':
			cerr << "Look project 4 mumual!!!" << endl;
			exit(0);
		case 'm':
			mode = optarg;
			if (mode == "MST")	basic = new Mst(out);
			else if (mode == "OPTTSP") basic = new Opttsp(out);
			else if (mode == "FASTTSP") basic = new FastTSP(out);
			else {
				cerr << "Error: invalid mode " << mode << endl;
				exit(1);
			}
			modeSpecified = true;
			break;

		default:
			cerr << "Error: invalid option " << endl;
			exit(1);
		}
	}

	if (!modeSpecified) {
		cerr << "Error: no mode specified" << endl;
		exit(1);
	}
}


int main(int argc, char ** argv) {
	ios_base::sync_with_stdio(false);
#ifdef DEBUG
	ostream& out = cout;
#else
	ostringstream sout;
	ostream& out = sout;
#endif // DEBUG

#ifndef DEBUG
	out << std::setprecision(2);
	out << std::fixed;
#endif

	cout << std::setprecision(2);
	cout << std::fixed;

	Basic* basic = nullptr;
	getMode(argc, argv, basic, out);

	basic->init();
	basic->work();

#ifndef DEBUG
	cout << sout.str();
#endif
    delete basic;
	return 0;
}
