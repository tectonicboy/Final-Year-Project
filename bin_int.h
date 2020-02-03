#ifndef BIN_INT_H
#define BIN_INT_H

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

typedef vector<bool> bvec;
typedef vector<bool>::size_type bvec_size;
typedef vector<bool>::iterator bvec_it;

unsigned short BITSIZE = 16;

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
		while (N.size() < BITSIZE) {
			N.push_back(false);
			++size;
		}
	};

	//Constructor from a vector of bools.
	bin_int(bvec S) : size(S.size()) {
		for (bvec_size i = 0; i < S.size(); ++i) {
			if (!S[i]) { N.push_back(false); }
			else { N.push_back(true); }
		}
		while (N.size() < BITSIZE) {
			N.push_back(false);
			++size;
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

	//Set a number to the maximum possible positive number that can be stored with BITSIZE bits.
	void set_max_pos() {
		for (bvec::iterator i = this->N.begin(); i < this->N.end() - 1; ++i) {
			*i = true;
		}
		*(this->N.end() - 1) = false;
	}

	//Set a number to the maximum possible negative number that can be stored with BITSIZE bits.
	void set_max_neg() {
		for (bvec::iterator i = this->N.begin(); i < this->N.end() - 1; ++i) {
			*i = false;
		}
		*(this->N.end() - 1) = true;
	}

	//Set a number to zero.
	void Nullify() {
		for (bvec_size s = 0; s < this->N.size(); ++s) {
			N[s] = false;
		}
	}


	void Update() {
		size = N.size();
	}

	void Negate() {
		bin_int zero(0);
		if (*this == zero) { return; }
		for (bvec_size i = 0; i < this->N.size(); ++i) {
			if (this->N[i]) { this->N[i] = false; }
			else { this->N[i] = true; }
		}
		string one = "1";
		bin_int One(one);
		*this += One;
	}

	bin_int operator+ (bin_int& X) {
		bool carry = false;
		bin_int R(X.N.size()), zero(X.N.size());
		for (bvec_size i = 0; i < X.N.size(); ++i) {
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
		if ((((*this > zero) && (X > zero)) && (R < zero)) || (((*this < zero) && (X < zero)) && (R > zero))) {
			cout << "*********************************************************************************\n";
			cout << "** ERROR: Arithmetic overflow: " << *this << " + " << X << "\n";
			cout << "*********************************************************************************\n";
		}
		return R;
	}

	bin_int operator- (bin_int& X) {
		if (*this == X) {
			bin_int zero(X.N.size());
			return zero;
		}
		bin_int R = X;
		R.Negate();
		R += *this;
		return R;
	}

	void operator>> (unsigned short x) {
		while (x > 0) {
			this->N.erase(this->N.end() - 1);
			this->N.insert(this->N.begin(), 1, false);
			--x;
		}
	}

	void operator<< (unsigned short x) {
		while (x > 0) {
			this->N.erase(this->N.begin());
			this->N.insert((this->N.end() - 1), 1, *(this->N.end() - 1));
			--x;
		}
	}


	//Printing a bin_int with an output stream. Definition outside class.
	friend ostream& operator<<(ostream& O, const bin_int& X);

	bin_int operator* (bin_int& X) {
		bin_int zero(0);
		if (*this == zero || X == zero) {
			return zero;
		}
		bool b1 = false, b2 = false, b3 = false;
		if ((this->N[this->N.size() - 1]) && (X.N[X.N.size() - 1])) {
			this->Negate();
			b1 = true;
			X.Negate();
			b2 = true;
		}
		if ((this->N[this->N.size() - 1]) && !(X.N[X.N.size() - 1])) {
			b3 = true;
			b1 = true;
			this->Negate();
		}
		if (!(this->N[this->N.size() - 1]) && (X.N[X.N.size() - 1])) {
			b3 = true;
			b2 = true;
			X.Negate();
		}
		bin_int R(X.size), Aux = *this;
		if (X.N[0]) {
			R += Aux;
		}
		for (bvec_size i = 1; i < X.N.size(); ++i) {
			Aux >> 1;
			if (X.N[i]) {
				R += Aux;
			}
		}
		if (b1) { this->Negate(); }
		if (b2) { X.Negate(); }
		if (b3) { R.Negate(); }
		if ((b3 && (!(R.N[R.N.size() - 1]))) || ((!b3) && (R.N[R.N.size() - 1]))) {
			cout << "*********************************************************************************\n";
			cout << "** ERROR: Arithmetic overflow: " << *this << " * " << X << "\n";
			cout << "*********************************************************************************\n";
		}
		return R;
	}

	bin_int operator/ (bin_int& Y) {
		bool b1 = false, b2 = false, b3 = false;
		bvec res;
		bin_int vec(0);
		if (Y == vec) {
			cout << "************************************************************************************\n";
			cout << "** ERROR: Just don't divide by zero: " << *this << " / " << Y << "\n";
			cout << "************************************************************************************\n";
			return vec;
		}
		if ((this->N[this->N.size() - 1]) && (Y.N[Y.N.size() - 1])) {
			this->Negate();
			Y.Negate();
			b2 = true;
			b1 = true;
		}
		if ((this->N[this->N.size() - 1]) && !(Y.N[Y.N.size() - 1])) {
			b3 = true;
			b1 = true;
			this->Negate();
		}
		if (!(this->N[this->N.size() - 1]) && (Y.N[Y.N.size() - 1])) {
			b3 = true;
			b2 = true;
			Y.Negate();
		}
		for (bvec_it it1 = this->N.end() - 1; it1 >= this->N.begin(); --it1) {
			vec.N.insert(vec.N.begin(), 1, *it1);
			vec.N.erase(vec.N.end() - 1);
			if (vec >= Y) {
				res.insert(res.begin(), 1, true);
				vec -= Y;
			}
			else {
				res.insert(res.begin(), 1, false);
			}
			if (it1 == this->N.begin()) {
				break;
			}
		}
		bin_int Result(res);
		if (b1) { this->Negate(); }
		if (b2) { Y.Negate(); }
		if (b3) { Result.Negate(); }
		return Result;
	}

	bool operator== (bin_int& X) {
		for (bvec_size i = 0; i < this->N.size(); ++i) {
			if ((this->N[i]) != (X.N[i])) { return false; }
		}
		return true;
	}

	bool operator!= (bin_int& X) {
		return !(*this == X);
	}
	bool operator< (bin_int& X) {
		if ((*(this->N.end() - 1)) && (!(*(X.N.end() - 1)))) { return true; }
		else if ((!(*(this->N.end() - 1))) && (*(X.N.end() - 1))) { return false; }
		else if ((!(*(this->N.end() - 1))) && (!(*(X.N.end() - 1)))) {
			for (bvec_size i = (X.N.size() - 2);; --i) {
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

	bool operator> (bin_int& X) {

		if ((!(*this < X)) && (!(*this == X))) {
			return true;
		}
		else {
			return false;
		}
	}

	bool operator>= (bin_int& X) {
		return (!(*this < X));
	}

	bool operator<= (bin_int& X) {
		return (!(*this > X));
	}

	void operator+= (bin_int& X) {
		*this = *this + X;
	}

	void operator-= (bin_int& X) {
		*this = *this - X;
	}

	void operator*= (bin_int& X) {
		*this = *this * X;
	}

	void operator/= (bin_int& X) {
		*this = *this / X;
	}

	void operator++ (void) {
		if (!this->N[this->N.size() - 1]) {
			for (bvec_size i = 0; i < this->N.size(); ++i) {
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
		if (!this->N[this->N.size() - 1]) {
			for (bvec_size i = 0; i < this->N.size(); ++i) {
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

bin_int min(bin_int& X, bin_int& Y) {
	if (X < Y) {
		return X;
	}
	else {
		return Y;
	}
}

bin_int max(bin_int& X, bin_int& Y) {
	if (X < Y) {
		return Y;
	}
	else {
		return X;
	}
}

bin_int abs(bin_int X) {
	
	if (X.N[X.N.size() - 1]) {
		X.Negate();
		return X;
	}
	else {
		return X;
	}
}

ostream& operator<<(ostream& O, const bin_int& X) {
	for (bvec_size i = 0; i < X.N.size(); ++i) {
		O << X.N[i];
	}
	return O;
}

#endif
