#ifndef SIMULT_SOLVER_H
#define SIMULT_SOLVER_H

#include <algorithm>
#include <vector>

using namespace std;

//The template function to find the Lowest Common Multiple of two numbers (whatever their encoding system is)
template <typename T>
T LCM(T a, T b) {
	T r0 = max(a, b), r1 = min(a, b), r2(0), gcd(0), lcm(0), aux(0), zero(0);
	bool b1 = true;
	vector<T> V;
	int x = 0;
	while (x == 0) {
		aux = r0 - r1;
		V.push_back(aux);
		while (aux >= zero) {

			aux -= r1;
			V.push_back(aux);
		}
		if ((*(V.end() - 2)) == zero) {
			gcd = *(V.end() - 3);
			break;
		}
		if (b1) {
			if (abs(*(V.end() - 1)) < *(V.end() - 2)) {
				b1 = false;
				r2 = abs(*(V.end() - 1));
			}
			else {
				b1 = true;
				r2 = *(V.end() - 2);
			}
		}
		else {
			b1 = true;
			if (*(V.end() - 2) < *(V.end() - 3)) {
				r2 = *(V.end() - 2);
			}
			else {
				r2 = *(V.end() - 3);
			}
		}
		r0 = r1, r1 = r2;
		V = {};
	}
	T c = (a * b);
	lcm = abs(c);
	T counter(0);
	while (lcm > zero) {
		++counter;
		lcm -= gcd;
	}
	return counter;
}

//Just so I can test it with ints
void Nullify(int & X){
	X = 0;
}


/*The template for solving a system of simultaneous equations is made such that the coefficients of the unknowns are of type T.
Furthermore, the template function assumes that the following functionality for type T exists:
0. There is a function called Nullify which intakes a variable of type T and makes it equal to zero.
1. operator-=, operator>=, operator++, operator--, operator+ and operator- are defined for type T.
2. You can instantiate a variable of type T equaling zero by writing T var_name(0), where 0 is an int.
*/
template <typename T>
void Solve (vector<vector<T>> V, int r, int c){
	int r_curr = 1, c_pivot = 0, r_pivot = 0;
	T aux, lcm, counter(0);
	while (c_pivot < c - 1) {
		while (r_curr <= r - 1) {
			lcm = LCM(V[r_pivot][c_pivot], V[r_curr][c_pivot]);
			aux = lcm;
			while(aux >= V[r_pivot][c_pivot]){ 
				++counter;
				aux -= V[r_pivot][c_pivot];
			}
			aux = counter;
			Nullify(counter);
			for (int F = 0; F < c; ++F) {
				while (V[r_curr][F] >= aux) {
					++counter;
					V[r_curr][F] -= aux;
				}
				V[r_curr][F] = counter;
				Nullify(counter);
			}
			aux = lcm;
			while (aux >= V[r_curr][c_pivot]) {
				++counter;
				aux -= V[r_curr][c_pivot];
			}
			aux = counter;
			Nullify(counter);
			for (int F = 0; F < c; ++F) {
				while (V[r_pivot][F] >= aux) {
	
					++counter;
					V[r_pivot][F] -= aux;
				}
				V[r_pivot][F] = counter;
				Nullify(counter);
			}
			for (int F = 0; F < c; ++F) {
				V[r_curr][F] -= V[r_pivot][F];
			}
			++r_curr;
		}
		++c_pivot;
		++r_pivot;
		r_curr = r_pivot; 
		++r_curr;
	}

	r_pivot = r - 1, c_pivot = c - 2, r_curr = r_pivot - 1;
	while (c_pivot > 0) {
		while (r_curr >= 0) {
			lcm = LCM(V[r_pivot][c_pivot], V[r_curr][c_pivot]);
			aux = lcm;
			while (aux >= V[r_pivot][c_pivot]) {
				++counter;
				aux -= V[r_pivot][c_pivot];
			}
			aux = counter;
			Nullify(counter);
			for (int F = 0; F < c; ++F) {
				while (V[r_curr][F] >= aux) {
					++counter;
					V[r_curr][F] -= aux;
				}
				V[r_curr][F] = counter;
				Nullify(counter);
			}
			aux = lcm;
			while (aux >= V[r_curr][c_pivot]) { 
				++counter;
				aux -= V[r_curr][c_pivot];
			}
			aux = counter;
			Nullify(counter);
			for (int F = 0; F < c; ++F) {
				while (V[r_pivot][F] >= aux) {
					++counter;
					V[r_pivot][F] -= aux;
				}
				V[r_pivot][F] = counter;
				Nullify(counter);
			}
			for (int F = 0; F < c; ++F) {
				V[r_curr][F] -= V[r_pivot][F];
			}
			--r_curr;
		}
		--c_pivot;
		--r_pivot;
		r_curr = r_pivot - 1;
	}

	for (int F = 0; F < r; ++F) {
		while (V[F][c - 1] >= V[F][F]) {
			++counter;
			V[F][c - 1] -= V[F][F];
		}
		V[F][c - 1] = counter;
		Nullify(counter);
		V[F][F] = 1;
	}

}


#endif
