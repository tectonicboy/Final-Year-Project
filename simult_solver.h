#ifndef SIMULT_SOLVER_H
#define SIMULT_SOLVER_H

#include <algorithm>
#include <vector>

using namespace std;

//The template function to find the Lowest Common Multiple of two numbers (whatever their encoding system is), implementing Euclid's Algorithm.
template <typename T>
T LCM(T a, T b) {
	T r0 = max(a, b), r1 = min(a, b), r2(0), gcd(0), lcm(0), aux(0), zero(0), r(0), e(0);
	cout << "Worked out MAX = "; r0.Print_Num(); cout << ", MIN = "; r1.Print_Num(); cout << "\n";
	bool wasE = false;
	vector<T> V;
	int x = 0;
	while (x == 0) {
		aux = r0 - r1;
		V.push_back(aux);
		if (wasE) {
			cout << "\tIt was E.\n";
			wasE = false;
			while (aux > r1) {
				aux -= r1;
				V.push_back(aux);
			}
			if ((*(V.end() - 2)) == zero) {
				gcd = r1;
				cout << "\t\t**** GCD = "; gcd.Print_Num(); cout << " *****\n";
				break;
			}
			r2 = *(V.end() - 1);
		}
		else {
			cout << "\tIt was not E.\n";
			while (aux >= zero) {
				aux -= r1;
				V.push_back(aux);
			}
			if ((*(V.end() - 2)) == zero) {
				gcd = r1;
				cout << "\t\t***** GCD = "; gcd.Print_Num(); cout << " *****\n";
				break;
			}
			e = abs(aux);
			r = *(V.end() - 2);
			if (e < r) {
				r2 = e;
				wasE = true;
			}
			else {
				r2 = r;
				wasE = false;
			}
			
		}
		cout << "\t\tNEW R = "; r2.Print_Num(); cout << "\n";
		r0 = r1, r1 = r2;
		V = {};
	}
	T c = (a * b);
	lcm = abs(c);
	T counter(0);
	int count = 0;
	cout << "Lastly, dividing abs(a*b) = "; lcm.Print_Num(); cout << " BY gcd = "; gcd.Print_Num(); cout << "\n";
	while (lcm > zero) {
		++count;
		if (count % 1000 == 0) { cout << "    COUNT = " << count << "\n"; }
		++counter;
		lcm -= gcd;
	}
	cout << "END COUNT = " << count << "\n";
	return counter;
}


void Nullify(int & X){
	X = 0;
}
/*The template for solving a system of simultaneous equations is made such that the coefficients of the unknowns are of type T.
Furthermore, the template function assumes that the following functionality for type T already exists:
0. There is a function with signature "void Nullify(T)" which makes the input number equal to zero.
1. operator-=, operator>=, operator++, operator--, operator+ and operator- are defined for type T.
2. You can instantiate a variable of type T equaling zero by writing "T var_name(0)", where 0 is an int.
*/
template <typename T>
void Solve (vector<vector<T>> V, int r, int c){
	int r_curr = 1, c_pivot = 0, r_pivot = 0;
	T aux, lcm, counter(0);
	//Loop to triangulate the matrix.
	while (c_pivot < c - 1) {
		//Loop defining what happens at each row.
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
	//Loop to triangulate the matrix again, producing an integer multiple of the solution matrix.
	while (c_pivot > 0) {
		//Loop defining what happens at each row.
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
	//Loop to produce the final solution matrix.
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
