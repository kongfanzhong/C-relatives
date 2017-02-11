/*
Simulate a simple excel...
Input a m*n matrix, and give expressions in each cell.
Output the value in each cell.
(C4 represents the value of the third row and the fourth coloum)
A possible input:
4 3
C4 B2 +
5 3 4 * /
B1
C4
C2
3 4 -- ++ *
3
7
2
5 -1 ++ *
6
5

*/

#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;


class Spreadsheet {
private:
	size_t rowNum, colNum; // the size of table
	struct Cell { // 
		bool visited;
		string content;
		double val;
	};
	vector< vector<Cell> > sheet;
	ostream & out;
	
	// see function descriptions below

	double getValue(string );
	void calcValue(Cell & thisCell);
	//void checkGood();
	//bool checkCell(Cell& thisCell);
public:
	Spreadsheet(ostream & myOut): out(myOut){

	}
	void init(); // read from std
	void work(); 
	void output();
};

inline void Spreadsheet::init() {
	cin >> colNum >> rowNum;
	string tempString; 
	getline(cin, tempString); // get rid of \n
	// resize the sheet first to reduce the cost of push_back()
	// reduce the usage of memory and time.
	sheet.resize(rowNum);
	for (size_t i = 0; i < rowNum; ++i) sheet[i].resize(colNum);

	for (size_t i = 0; i < rowNum; ++i)
		for (size_t j = 0; j < colNum; ++j) {
			getline(cin, sheet[i][j].content);
			sheet[i][j].visited = false;
			sheet[i][j].val = numeric_limits<double>::max();
		}
	

}
// If the data has large chance to be Circular dependency, then we can build a seperate test at first.
// Otherwise, we do not need the functions below
// "make common case faster"
// child_list is a vector contains all cells are needed to calculate this cell. (should be initialized in init() function if needed).

// O(V+E)
/*
bool Spreadsheet::checkCell(Cell & thisCell) {
	if (thisCell.visited) return true;
	else if (thisCell.onPath) return false;
	else {
		thisCell.onPath = true;
		for (auto x : thisCell.child_list)
			if (checkCell(*x)) ;
			else return false;
	}
	return true;
}
inline void Spreadsheet::checkGood() {
	for (auto & x : sheet) {
		for (auto & y : x) {
			checkCell(y);
			y.visited = true;
		}
	}
	out << "Error: Circular dependency!\n";
	exit(0);
} 
*/

// This function give back the value inStr represents
// 'A1' will return the value in cell 'A1', e.g. 3
// '3' will return '3'
inline double Spreadsheet::getValue(string inStr) {
	if (isalpha(inStr[0])) { // If have dependence
		int deRow = inStr[0] - 'A', deCol = atoi(inStr.substr(1, inStr.size() - 1).c_str()) - 1;
		if (sheet[deRow][deCol].visited) {
			if (sheet[deRow][deCol].val == numeric_limits<double>::max()) { // if return to a cell on the dependence path
				// Actually should be cerr (however the problem ask us to use cout)
				cout << "Error: Circular dependency!" << endl;
				exit(0);
			}
			else return sheet[deRow][deCol].val;
		}
		else { // if this cell has been calculated
			calcValue(sheet[deRow][deCol]);
			return sheet[deRow][deCol].val;
		}
	}
	else return (double) atoi(inStr.c_str());
}

inline void error_badExp() {
	cout << "Bad expressions!" << endl;
	exit(0);
}
//This function trys to calculate the value of thisCell
//Suppose no error in expressions!
//If an expression is 3 3*2, then it will lead to the crash of the algorithm.

inline void Spreadsheet::calcValue(Cell & thisCell) {

	istringstream temp(thisCell.content);
	string tempString;
	deque<double> myDeq;

	thisCell.visited = true;
	while (temp >> tempString) {
		if (tempString == "++")
			myDeq.back()++;
		else if (tempString == "--")
			myDeq.back()--;
		else if (tempString == "+") {
			if (myDeq.size() < 2) error_badExp();
			double oper2 = myDeq.back(); myDeq.pop_back();
			double oper1 = myDeq.back(); myDeq.pop_back();
			myDeq.push_back(oper1 + oper2);
		}
		else if (tempString == "-") {
			if (myDeq.size() < 2) error_badExp();
			double oper2 = myDeq.back(); myDeq.pop_back();
			double oper1 = myDeq.back(); myDeq.pop_back();
			myDeq.push_back(oper1 - oper2);
		}
		else if (tempString == "*") {
			if (myDeq.size() < 2) error_badExp();
			double oper2 = myDeq.back(); myDeq.pop_back();
			double oper1 = myDeq.back(); myDeq.pop_back();
			myDeq.push_back(oper1 * oper2);

		}
		else if (tempString == "/") {
			if (myDeq.size() < 2) error_badExp();
			double oper2 = myDeq.back(); myDeq.pop_back();
			double oper1 = myDeq.back(); myDeq.pop_back();
			if (oper2 == 0) {
				cout << "Divided by 0" << endl;
				exit(0);
			}
			myDeq.push_back(oper1 / oper2);
		}
		else // we can add if sentence to check if tempString is in format 'A1' or '2123'
			myDeq.push_back(getValue(tempString));
		
	}
	if (myDeq.size() > 1) error_badExp();
	thisCell.val = myDeq.front();
}

// work function
inline void Spreadsheet::work() {
	//checkGood();
	for (auto &row : sheet) {
		for (auto &cell : row) {
			if (cell.visited == true) continue;
			calcValue(cell);
		}
	}

}
// output function
inline void Spreadsheet::output() {
	out << setprecision(5) << fixed;
	for (auto &row : sheet) {
		for (auto &cell : row) {
			out << cell.val << "\n";
		}
	}
}


int main() {
	ios_base::sync_with_stdio(false);
// We can switch our output from ostringstream to standard output based on if we are more lack of memory or time
// If we need time and have a lot of things to output, ostringstream will be better.
// Otherwise, we may choose cout. (Switch by defining DEBUG)
#ifdef DEBUG
	ostream& out = cout;
#else
	ostringstream sout;
	ostream& out = sout;
#endif // DEBUG

	Spreadsheet mySheet(out);
	mySheet.init();
	mySheet.work();
	mySheet.output();

#ifndef DEBUG
	cout << sout.str();
#endif // !DEBUG

	return 0;
}