#include <iostream>
#include <vector>

#include "bin_int.h"
#include "simult_solver.h"

using namespace std;

int main(void) {
	cout << "\t******* TESTING LCM TEMPLATE FUNCTION WITH BINARY LIBRARY *******\n\n";
	int i = 0;
	while (i == 0) {
		string s1, s2;
		cout << "\nPlease input the 2 binary numbers (one per line) to find the LCM of.\n";
		cin >> s1 >> s2;
		bin_int n1(s1), n2(s2), n3 = (LCM(n1, n2));
		cout << "LCM = "; n3.Print_Num(); cout << "\n";
	}
	return 0;
}
