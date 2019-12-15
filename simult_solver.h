#ifndef SIMULT_SOLVER_H
#define SIMULT_SOLVER_H

#include <algorithm>
#include <vector>

using namespace std;

//The template function to find the Lowest Common Multiple of two numbers (whatever their encoding system is), implementing Euclid's Algorithm.
template <typename T>
T LCM(T &a, T &b) {
	bool b1 = false, b2 = false;
	T zero(0);
	if (a < zero) {
		b1 = true;
		a.Negate();
	}
	if (b < zero) {
		b2 = true;
		b.Negate();
	}
	if ((a == zero) || (b == zero)) {
		cout << "ERROR: LCM can't take zero as input.\n";
		return zero;
	}
	T r0 = max(a, b), r1 = min(a, b), r2(0), gcd(0), lcm(0), aux(0), r(0), e(0);
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
				goto l1;
			}
			r2 = *(V.end() - 1);
		}
		else {
			while (aux >= zero) {
				aux -= r1;
				V.push_back(aux);
			}
			if ((*(V.end() - 2)) == zero) {
				gcd = r1;
				goto l1;
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
		r0 = r1, r1 = r2;
		V = {};
	}
	l1:
	T c = (a * b);
	lcm = abs(c);
	lcm /= gcd;
	if (b1) { a.Negate(); }
	if (b2) { b.Negate(); }
	cout << "LCM = "; lcm.Print_Num(); cout << "\n";
	return lcm;
}


/*The template for solving a system of simultaneous equations is made such that the coefficients of the unknowns are of type T.
Furthermore, the template function assumes that the following functionality for type T already exists:
0. There is a function with signature "void Nullify(T)" which makes the input number equal to zero.
1. operator-=, operator>=, operator++, operator--, operator+ and operator- are defined for type T.
2. You can initialize a variable of type T equaling zero by writing "T var_name(0)", where 0 is an int.
*/
template <typename T>
void Solve (vector<vector<T>> &V, int r, int c){
	int r_curr = 1, c_pivot = 0, r_pivot = 0;
	T lcm(0), pivot(0), current(0), pivaux(0), curraux(0), zero(0), XX(0), YY(0);
	vector<T> PivotRow, CurrentRow;
	//Loop to triangulate the matrix.
	while (c_pivot < c - 2) {
		PivotRow = V[r_pivot];
		pivot = V[r_pivot][c_pivot];
		//Loop defining what happens at each row.
		while (r_curr <= r - 1) {
			cout << "Entered. row_current = " << r_curr << "\n";
			CurrentRow = V[r_curr];
			current = V[r_curr][c_pivot];
			if (current != zero) {
				if (current == pivot) {
					goto label1;
				}
				if (pivot == zero) {
					for (auto i = 0; (i < PivotRow.size()); ++i) {
						CurrentRow[i] *= PivotRow[i];
					}
				}
				else {
					lcm = LCM(pivot, current);
					XX = abs(pivot);
					YY = abs(current);
					pivaux = lcm/XX ;
					curraux = lcm/YY;
					for (auto i = 0; i < PivotRow.size(); ++i) {
						PivotRow[i] *= pivaux;
						CurrentRow[i] *= curraux;
					}
					label1:
					//Both signs are the same.
					if ( ((pivot > zero) && (current > zero)) || ((pivot < zero) && (current < zero)) ) {
						for (auto i = 0; i < PivotRow.size(); ++i) {
							CurrentRow[i] -= PivotRow[i];
						}
					}
					//The signs are different.
					else if (((pivot > zero) && (current < zero)) || ((pivot < zero) && (current > zero))) {
						for (auto i = 0; i < PivotRow.size(); ++i) {
							CurrentRow[i] += PivotRow[i];
						}
					}
					V[r_curr] = CurrentRow;
				}
			}
			++r_curr;
		}
		++c_pivot;
		++r_pivot;
		r_curr = r_pivot + 1; 
	}
	cout << "The matrix after 1st reduction:\n";
	for (auto i = 0; i < V.size(); ++i) {
		for (auto j = 0; j < (V[i]).size(); ++j) {
			(V[i][j]).Print_Num(); cout << " ";
		}
		cout << "\n";
	}
	r_pivot = r - 1, c_pivot = c - 2, r_curr = r_pivot - 1;
	//Loop to triangulate the matrix again.
	while (c_pivot > 0) {
		PivotRow = V[r_pivot];
		pivot = V[r_pivot][c_pivot];
		//Loop defining what happens at each row.
		while (r_curr >= 0) {
			cout << "Entered. row_current = " << r_curr << "\n";
			CurrentRow = V[r_curr];
			current = V[r_curr][c_pivot];
			if (current != zero) {
				if (pivot == zero) {
					for (auto i = 0; i < PivotRow.size(); ++i) {
						CurrentRow[i] *= PivotRow[i];
					}
				}
				else {
					lcm = LCM(pivot, current);
					XX = abs(pivot);
					YY = abs(current);
					pivaux = lcm / XX;
					curraux = lcm / YY;
					for (auto i = 0; i < PivotRow.size(); ++i) {
						PivotRow[i] *= pivaux;
						CurrentRow[i] *= curraux;
					}
					//Both signs are the same.
					if (((pivot > zero) && (current > zero)) || ((pivot < zero) && (current < zero))) {
						for (auto i = 0; i < PivotRow.size(); ++i) {
							CurrentRow[i] -= PivotRow[i];
						}
					}
					//The signs are different.
					else if (((pivot > zero) && (current < zero)) || ((pivot < zero) && (current > zero))) {
						for (auto i = 0; i < PivotRow.size(); ++i) {
							CurrentRow[i] += PivotRow[i];
						}
					}
					V[r_curr] = CurrentRow;
				}
			}
			--r_curr;
		}
		--c_pivot;
		--r_pivot;
		r_curr = r_pivot - 1;
	}
	cout << "The matrix after 2nd reduction:\n";
	for (auto i = 0; i < V.size(); ++i) {
		for (auto j = 0; j < (V[i]).size(); ++j) {
			(V[i][j]).Print_Num(); cout << " ";
		}
		cout << "\n";
	}
	//Loop to produce the final solution matrix by dividing at each row.
	for (int F = 0; F < r; ++F) {
		V[F][c - 1] /= V[F][F];
		V[F][F] /= V[F][F];
	}
}
#endif
