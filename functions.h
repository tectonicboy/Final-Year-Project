#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <iostream>
#include <vector>

constexpr unsigned short int max_size = 512;

using namespace std;

class bin_num {

public:
	unsigned short int size;
	bool N[max_size];
	bool MSB, LSB;
	//Constructor from a string containing 0s and 1s.
	bin_num(string S) : size(S.size()) {
		short int index = 0;
		for (int i = 0; i < S.size(); ++i) {
			if (S[i] == '0') { N[index] = false; }
			else if (S[i] == '1') { N[index] = true; }
			else { cout << "WARNING: Construction string contains characters other than '0' and '1'.\n"; }
			++index;
		}
		MSB = N[S.size() - 1];
		LSB = N[0];
	};

	//Constructor from a vector of bools.
	bin_num(vector<bool>S) : size(S.size()), LSB(*(S.begin())), MSB(*(S.end() - 1)) {
		short int index = 0;
		for (int i = 0; i < S.size(); ++i) {
			if (S[i] == 0) { N[index] = false; }
			else { N[index] = true; }
			++index;
		}
	}
	//Default constructor.
	bin_num() : size(max_size), MSB(false), LSB(false) {};


	void Print_Num() {
		for (int i = 0; i < this->size; ++i) {
			cout << this->N[i] << " ";
		}
		cout << "\n";
	}
};

bin_num smaller(const bin_num &X, const bin_num &Y) {
	if (X.size > Y.size) { return Y; }
	else { return X; }
}

bin_num bigger(const bin_num &X, const bin_num &Y) {
	if (X.size > Y.size) { return X; }
	else { return Y; }
}

bin_num Add_Two(const bin_num &X, const bin_num &Y) {
	bin_num* p1 = &(bigger(X, Y));
	bin_num* p2 = &(smaller(X, Y));
	bool carry = false;
	bin_num R;
	short int counter = -1;
	for (int i = 0; i <= (*p2).size - 1; ++i) {
		++counter;
		if (carry) {
			if ((X.N[i] && !Y.N[i]) || (!X.N[i] && Y.N[i])) {
				R.N[i] = false;
				carry = true;
			}
			else if (!X.N[i] && !Y.N[i]) {
				R.N[i] = true;
				carry = false;
			}
			else if (X.N[i] && Y.N[i]) {
				R.N[i] = true;
				carry = true;
			}
		}
		else {
			if ((X.N[i] && !Y.N[i]) || (!X.N[i] && Y.N[i])) {
				R.N[i] = true;
				carry = false;
			}
			else if (!X.N[i] && !Y.N[i]) {
				R.N[i] = false;
				carry = false;
			}
			else if (X.N[i] && Y.N[i]) {
				R.N[i] = false;
				carry = true;
			}
		}
	}

	++counter;
	while (carry) {
		if ((*p1).N[counter]) {
			R.N[counter] = false;
		}
		else { 
			R.N[counter] = true;
			break;
		}
		++counter;
	}
	++counter;

	while (counter <= (*p1).size - 1) {
		R.N[counter] = (*p1).N[counter];
		++counter;
	}

	R.size = (*p1).size;
	return R;
}


#endif
