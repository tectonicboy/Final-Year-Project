#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include "bin_int.h"
#include "functions.h"

typedef vector<bool> bvec;
typedef vector<bool>::iterator bvec_it;

using namespace std;

int main(void) {
	//To test the system automatically and exhaustively.
	/*
	string ss1 = "0", ss2 = "11111111000", ss3 = "1000000011111111";
	bin_int Zero(ss1), Max(ss2), Max_Neg(ss3);
	bvec vec1;
	for (bin_int test1 = Zero; test1 <= Max; ++test1) {
		for (bin_int test2 = Zero; test2 <= Max; ++test2) {
			vec1 = ToomCook(test1, test2, 3);
			for (bvec_it it1 = vec1.begin(); it1 != vec1.end(); ++it1) {
				cout << *it1;
			}
			cout << "\n";
		}
	}
	*/
	
	
	//To test the system manually.
	string s1 = "", s2 = "";
	int k = 0;
	for (int i = 0; i < 1;) {
		cout << "TESTING TOOM-COOK FUNCTION.\n";
		cout << "Enter the two numbers, lsb is the leftmost bit.\n";
		cin >> s1 >> s2;
		bin_int N1(s1), N2(s2);
		cout << "Enter k for splitting.\n";
		cin >> k;
		bvec product = ToomCook(N1, N2, k);
		for (bvec_it it1 = product.begin(); it1 != product.end(); ++it1) {
			cout << *it1 << "\n";
		}
	}
	return 0;
}
