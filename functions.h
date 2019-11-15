#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

typedef vector<bool>::size_type bvec_size;
typedef vector<bool> bvec;

class bin_num {

public:
	bvec_size size;
	bvec N;
	bool MSB;
	bool LSB;
	string name = "";
	//Constructor from a string containing 0s and 1s.
	bin_num(string S) : size(S.size()) {
		for (bvec_size i = 0; i < S.size(); ++i) {
			if (S[i] == '0') { N.push_back(false); }
			else if (S[i] == '1') { N.push_back(true); }
			else { cout << "WARNING: Construction string contains characters other than '0' and '1'.\n"; }
		}
		MSB = N[S.size() - 1];
		LSB = N[0];
	};

	//Constructor from a vector of bools.
	bin_num(bvec S) : size(S.size()), LSB(*(S.begin())), MSB(*(S.end() - 1)) {
		for (bvec_size i = 0; i < S.size(); ++i) {
			if (!S[i]) { N.push_back(false); }
			else { N.push_back(true); }
		}
		MSB = &(N[S.size() - 1]);
		LSB = N[0];
	}
	//Constructor from a size. Initializes all bits to 0.
	bin_num(bvec_size k) : size(k), MSB(false), LSB(false) {
		for (bvec_size i = 0; i < k; ++i) {
			N.push_back(0);
		}
	};

	
	void Print_Num() const {
		for (bvec_size i = 0; i < this->size; ++i) {
			cout << this->N[i];
		}
		cout << "\n";
	}

	void Update() {
		while (!*(N.end() - 1)) {
			N.erase(N.end() - 1);
			--size;
		}
		LSB = *(N.begin());
		MSB = *(N.end() - 1);
		size = N.size();
	}

	void Negate() {
		bvec_size i = 0;
		while (i < this->size) {
			if (this->N[i]) { this->N[i] = false; }
			else { this->N[i] = true; }
			++i;
		}
		cout << "\t\t\tInverted the number: ";
		this->Print_Num();
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
		if (!found) {
			this->N.push_back(true);
			++this->size;
		}
		cout << "\t\t\tAdded one to it: ";
		this->Print_Num();

	}


	bin_num* smaller(bin_num &X) {
		bin_num* ptr;
		if (X.size > this->size) { 
			ptr = this;
			return ptr;
		}
		else {
			ptr = &X;
			return ptr;;
		}
	}

	bin_num* bigger(bin_num &X) {
		bin_num* ptr;
		if (X.size > this->size) {
			ptr = &X;
			return ptr;
		}
		else { 
			ptr = this;
			return ptr;
		}
	}

	bin_num operator+ (bin_num & X) {
		this->name = "Katya", X.name = "Boiko";
		bin_num* p1;
		bin_num* p2;
		if (this->size != X.size) {
			p1 = (X.bigger(*this));
			p2 = (X.smaller(*this));
		}
		else {
			p1 = &X;
			p2 = &(*this);
		}
		cout << "p1 is pointing to " << p1->name << ", p2 is pointing to " << p2->name << "\n";
		cout << "Numbers we're adding:\n";
		for (bvec_size i = 0; i < p1->size; ++i) {
			cout << p1->N[i];
		}
		cout << "\n";
		for (bvec_size i = 0; i < p2->size; ++i) {
			cout << p2->N[i];
		}
		cout << "\n";
		bool carry = false;
		bin_num R(p1->size);
		short int counter = 0;
		for (bvec_size i = 0; i <= p2->size - 1; ++i) {
			++counter;			
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
		while ((carry) && (counter != p1->size)) {
			if (p1->N[counter]) {
				R.N[counter] = false;
			}
			else {
				R.N[counter] = true;
				carry = false;
				break;
			}
			++counter;
		}
		if (carry) { R.N.push_back(true); }
		++counter;

		while (counter <= p1->size - 1) {
			R.N[counter] = p1->N[counter];
			++counter;
		}

		R.Update();
		return R;
	}

	bin_num operator- (bin_num X) {
		cout << "Input number is: ";
		X.Print_Num();
		X.Negate();
		cout << "Negated number is now: ";
		X.Print_Num();
		cout << "\n";
		bin_num R = *this + X;
		cout << "And Result is: ";
		R.Print_Num();
		return R;
	}

	bin_num operator* (bin_num & X) {
		bin_num R(this->size + X.size), Aux = *this;
		if (X.N[0]) { R = R + Aux; }
		for (bvec_size i = 1; i < X.size; ++i) {
			Aux.N.insert(Aux.N.begin(), 1, 0);
			++Aux.size;
			if (X.N[i]) {
				R = R + Aux;
			}
		}
		R.Update();
		return R;
	}


};


#endif
