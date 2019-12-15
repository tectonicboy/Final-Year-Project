#ifndef BIN_INT_H
#define BIN_INT_H

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<bool>::size_type bvec_size;
typedef vector<bool> bvec;

#define BITSIZE 16

class bin_int {
public:
	bvec_size size;
	bvec N;

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
	};

	//Constructor from a size. Initializes all bits to 0.
	bin_int(bvec_size k) : size(k) {
		for (bvec_size i = 0; i < k; ++i) {
			N.push_back(0);
		}
	};

	//Constructor from a zero int. Initializes all bits to 0.
	bin_int(int a) : size(BITSIZE) {
		if (a == 0) {
			while (a < BITSIZE) {
				N.push_back(false);
				++a;
			}
		}
	}


	void Nullify() {
		for (bvec_size s = 0; s < this->size; ++s) {
			N[s] = false;
		}
	}

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

	bin_int operator+ (bin_int & X) {
		bool carry = false;
		bin_int R(X.size);
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

		R.Update();
		return R;
	}

	bin_int operator- (bin_int & X) {
		if (*this == X) {
			bin_int zero(X.size);
			return zero;
		}
		bin_int R = X;
		R.Negate();
		R += *this;
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
		bool b1 = false, b2 = false, b3 = false;
		//If both are negative
		if ((this->N[this->size - 1]) && (X.N[X.size - 1])) {
			this->Negate();
			b1 = true;
			X.Negate();
			b2 = true;
		}
		if ((this->N[this->size - 1]) && !(X.N[X.size - 1])) {
			b3 = true;
			b1 = true;
			this->Negate();
		}
		if (!(this->N[this->size - 1]) && (X.N[X.size - 1])) {
			b3 = true;
			b2 = true;
			X.Negate();
		}
		bin_int R(X.size), Aux = *this;
		if (X.N[0]) {
			R = R + Aux;

		}
		for (bvec_size i = 1; i < X.size; ++i) {
			Aux >> 1;
			if (X.N[i]) {
				R = R + Aux;

			}
		}
		if (b1) { this->Negate(); }
		if (b2) { X.Negate(); }
		if (b3) { R.Negate(); }
		return R;
	}

	bin_int operator/ (bin_int & X) {
		bool b1 = false, b2 = false, b3 = false;
		bin_int counter(0), zero(0);
		if (X == zero) {
			cout << "ERROR: Just don't divide by zero.\n";
			return zero;
		}
		if (*this == zero) { return zero; }
		if ((this->N[this->size - 1]) && (X.N[X.size - 1])) {
			this->Negate();
			b1 = true;
			X.Negate();
			b2 = true;
		}
		if ((this->N[this->size - 1]) && !(X.N[X.size - 1])) {
			b3 = true;
			b1 = true;
			this->Negate();
		}
		if (!(this->N[this->size - 1]) && (X.N[X.size - 1])) {
			b3 = true;
			b2 = true;
			X.Negate();
		}
		while (*this > zero) {
			*this -= X;
			++counter;
		}
		if (b1) { this->Negate(); }
		if (b2) { X.Negate(); }
		if (b3) { counter.Negate(); }
		return counter;
	}

	bool operator== (bin_int & X) {
		for (bvec_size i = 0; i < this->size; ++i) {
			if ((this->N[i]) != (X.N[i])) { return false; }
		}
		return true;
	}

	bool operator!= (bin_int & X) {
		return !(*this == X);
	}
	bool operator< (bin_int & X) {
		if ((*(this->N.end() - 1)) && (!(*(X.N.end() - 1)))) { return true; }
		else if ((!(*(this->N.end() - 1))) && (*(X.N.end() - 1))) { return false; }
		else if ((!(*(this->N.end() - 1))) && (!(*(X.N.end() - 1)))) {
			for (bvec_size i = (X.size - 2);; --i) {
				if (i == 0) {
					if ((this->N[i]) && (!(X.N[i]))) {
						return false;
					}
					if ((!(this->N[i])) && (X.N[i])) {
						return true;
					}
					break;
				}
				else {
					if ((this->N[i]) && (!(X.N[i]))) {
						return false;
					}
					if ((!(this->N[i])) && (X.N[i])) {
						return true;
					}
				}
			}
			return false;
		}
		else {
			bin_int N1 = *this, N2 = X;
			N1.Negate();
			N2.Negate();
			return (N1 > N2);
		}

	}
	//*this > X
	bool operator> (bin_int & X) {

		if ((!(*this < X)) && (!(*this == X))) {
			return true;
		}
		else {
			return false;
		}
	}

	bool operator>= (bin_int & X) {
		return (!(*this < X));
	}

	bool operator<= (bin_int & X) {
		return (!(*this > X));
	}

	void operator+= (bin_int & X) {
		*this = *this + X;
	}

	void operator-= (bin_int & X) {
		*this = *this - X;
	}

	void operator*= (bin_int & X) {
		*this = *this * X;
	}

	void operator/= (bin_int & X) {
		*this = *this / X;
	}

	void operator++ (void) {
		if (!this->N[this->size - 1]) {
			for (bvec_size i = 0; i < this->size; ++i) {
				if (this->N[i]) {
					this->N[i] = false;
				}
				else {
					this->N[i] = true;
					break;
				}
			}
		}
		else {
			this->Negate();
			--(*this);
			this->Negate();
		}
	}

	void operator-- (void) {
		if (!this->N[this->size - 1]) {
			for (bvec_size i = 0; i < this->size; ++i) {
				if (!this->N[i]) {
					this->N[i] = true;
				}
				else {
					this->N[i] = false;
					break;
				}
			}
		}
		else {
			this->Negate();
			++(*this);
			this->Negate();
		}
	}
};

bin_int min(bin_int & X, bin_int & Y) {
	if (X < Y) {
		return X;
	}
	else {
		return Y;
	}
}

bin_int max(bin_int & X, bin_int & Y) {
	if (X < Y) {
		return Y;
	}
	else {
		return X;
	}
}

bin_int abs(bin_int & X) {
	if (X.N[X.size - 1]) {
		bin_int p = X;
		p.Negate();
		return p;
	}
	else {
		bin_int p = X;
		return p;
	}
}
#endif
