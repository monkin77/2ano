#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

int main() {
	double nextVal = exp(-1);
	for (int i = 1; i <= 25; i++) {
		nextVal = i * nextVal - 1;
		cout << "val: " << fixed << setprecision(20) << nextVal << endl;
	}
}