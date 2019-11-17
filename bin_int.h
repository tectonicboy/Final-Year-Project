#ifndef BIN_INT_H
#define BIN_INT_H

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<bool>::size_type bvec_size;
typedef vector<bool> bvec;

class bin_int {
public:
	bvec_size size;
	bvec N;
	bool TwosComp;
	//Constructor from a string containing 0s and 1s.
	bin_int(string S) : size(S.size()) {
		for (bvec_size i = 0; i < S.size(); ++i) {
			if (S[i] == '0') { N.push_back(false); }
			else if (S[i] == '1') { N.push_back(true); }
			else { cout << "WARNING: Construction string contains characters other than '0' and '1'.\n"; }
		}

	};

	//Constructor from a vector of bools.
	bin_int(bvec S) : size(S.size()) {
		for (bvec_size i = 0; i < S.size(); ++i) {
			if (!S[i]) { N.push_back(false); }
			else { N.push_back(true); }
		}
	}
	//Constructor from a size. Initializes all bits to 0.
	bin_int(bvec_size k) : size(k) {
		for (bvec_size i = 0; i < k; ++i) {
			N.push_back(0);
		}
	};

	void Print_Num() const {
		for (bvec_size i = 0; i < this->size; ++i) {
			cout << this->N[i];
		}
	}

	void Update() {
		size = N.size();
	}

	void Negate() {
		bvec_size i = 0;
		while (i < this->size) {
			if (this->N[i]) { this->N[i] = false; }
			else { this->N[i] = true; }
			++i;
		}
		i = 0;
		bool found = false;
		while (i < this->size && !found) {
			if (this->N[i]) {
				this->N[i] = false;
			}
			else {
				this->N[i] = true;
				found = true;
			}
			++i;
		}
	}

	bin_int* smaller(bin_int &X) {
		bin_int* ptr;
		if (X.size > this->size) { 
			ptr = this;
			return ptr;
		}
		else {
			ptr = &X;
			return ptr;;
		}
	}

	bin_int* bigger(bin_int &X) {
		bin_int* ptr;
		if (X.size > this->size) {
			ptr = &X;
			return ptr;
		}
		else { 
			ptr = this;
			return ptr;
		}
	}

	bin_int operator+ (bin_int & X) {
		bool carry = false;
		bin_int R(X.size + 1);
		for (bvec_size i = 0; i < X.size; ++i) {
			if (carry) {
				if ((X.N[i] && !this->N[i]) || (!X.N[i] && this->N[i])) {
					R.N[i] = false;
					carry = true;
				}
				else if (!X.N[i] && !this->N[i]) {
					R.N[i] = true;
					carry = false;
				}
				else if (X.N[i] && this->N[i]) {
					R.N[i] = true;
					carry = true;
				}
			}
			else {
				if ((X.N[i] && !this->N[i]) || (!X.N[i] && this->N[i])) {
					R.N[i] = true;
					carry = false;
				}
				else if (!X.N[i] && !this->N[i]) {
					R.N[i] = false;
					carry = false;
				}
				else if (X.N[i] && this->N[i]) {
					R.N[i] = false;
					carry = true;
				}
			}
		}

		if (carry) { *(R.N.end() - 1) = true; }
		else { R.N.erase(R.N.end() - 1); }

		R.Update();
		return R;
	}

	bin_int operator- (bin_int X) {
		if (*this == X) {
			string zero = "0";
			bin_int Zero(zero);
			return Zero;
		}
		X.Negate();
		bin_int R = *this + X;
		if (R.size > X.size) { R.N.erase(R.N.end() - 1); --R.size; }
		return R;
	}

	void operator>> (unsigned short int x) {
		while (x > 0) {
			this->N.erase(this->N.end() - 1);
			this->N.insert(this->N.begin(), 1, false);
			--x;
		}
	}

	bin_int operator* (bin_int & X) {
		bin_int R(this->size + X.size), Aux = *this;
		while (Aux.size < R.size) {
			Aux.N.insert(Aux.N.begin(), 1, false);
			++Aux.size;
		}
		if (X.N[0]) { R = R + Aux; }
		for (bvec_size i = 1; i < X.size; ++i) {
			Aux >> 1;
			if (X.N[i]) {
				R = R + Aux;
			}
		}
		if (!(*(R.N.end() - 1))) { 
			R.N.erase(R.N.end() - 1);
			--R.size;
		}
		R.Update();
		return R;
	}
	
	bool operator== (bin_int & X) {
		bvec_size s = (*(X.smaller(*this))).size;
		bin_int* ptr = X.bigger(*this);
		for (bvec_size i = 0; i < s; ++i) {
			if (this->N[i] != X.N[i]) { return false; }
		}
		while (s < ptr->size) {
			if (ptr->N[s]) { return false; }
			++s;
		}
	}

};


#endif
