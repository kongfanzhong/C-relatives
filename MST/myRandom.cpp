#include <algorithm>
#include <ctime>
#include <random>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>

using namespace std;
int myRand(const int MAX) {
	int myOut = rand() % MAX;
	myOut -= (MAX / 2);
	return myOut;

}
int main() {
	const int N = 10;
	const int MAX = 20;
	cout << N << endl;
	for (int i = 0; i < N; i++) {
		cout << myRand(MAX) << " " << myRand(MAX) << endl;

	}
}
