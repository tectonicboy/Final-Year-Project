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
				goto l3;
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
				goto l3;
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
	l3:
	T c = (a * b);
	lcm = abs(c);
	lcm /= gcd;
	if (b1) { a.Negate(); }
	if (b2) { b.Negate(); }
	//cout << "LCM = "; lcm.Print_Num(); cout << "\n";
	return lcm;
}


/*The template for solving a system of simultaneous equations is made such that the coefficients of the unknowns are of type T.
Furthermore, the template function assumes that the following functionality for type T already exists:
0. There is a function with signature "void Nullify(T)" which makes the input number equal to zero.
1. operator-=, operator>=, operator++, operator--, operator+ and operator- are defined for type T.
2. You can initialize a variable of type T equaling zero by writing "T var_name(0)", where 0 is an int.
*/
template <typename T>
void Solve (vector<vector<T>> &V){
	short int rows = V.size(), columns = V[0].size(), r_curr = 1, r_pivot = 0, c_pivot = 0;
	T pivot = V[0][0], current = V[0][1], zero(0), lcm(0);
	vector<T> PivotRow, CurrentRow;
	//First triangulation loop.
	while (r_pivot <= rows - 2) {
		pivot = V[r_pivot][c_pivot];
		PivotRow = V[r_pivot];
		cout << "PivotRow = " << r_pivot << ", pivot = "; pivot.Print_Num(); cout << "\n";
		//What happens at each row.
		while (r_curr <= rows - 1) {
			current = V[r_curr][c_pivot];
			CurrentRow = V[r_curr];
			cout << "\tCurrent row = " << r_curr << "\n";
			cout << "\tcurrent = "; current.Print_Num(); cout << "\n";
			if (current != zero) {
				cout << "\tcurrent is not zero.\n";
				if (pivot == zero) {
					cout << "\t\tpivot is zero. Multiplying current row by pivot row.\n";
					//If pivot is zero, multiply the current row by the pivot row.
					for (short int i = 0; i < columns; ++i) {
						CurrentRow[i] *= PivotRow[i];
					}
				}
				else {
					cout << "\t\tpivot is not zero.\n";
					if (pivot == current) { cout << "\t\tpivot = current.\n"; goto l1; }
					//Find the lowest common multiple of the pivot and the current number.
					lcm = LCM(pivot, current);
					cout << "\t\tLCM = "; lcm.Print_Num(); cout << "\n";
					//Calculate the absolute values.
					pivot = abs(pivot);
					current = abs(current);
					cout << "\t\tabs(pivot) = "; pivot.Print_Num(); cout << ", abs(current) = "; current.Print_Num(); cout << "\n";
					//These are the numbers we'll multiply the pivot row and current row by.
					pivot = lcm / pivot;
					current = lcm / current;
					cout << "\t\tNumber to multiply pivot row by: "; pivot.Print_Num(); cout << "\n";
					cout << "\t\tNumber to multiply current row by: "; current.Print_Num(); cout << "\n";
					//Multiply the rows by the resulting numbers.
					for (short int i = 0; i < columns; ++i) {
						CurrentRow[i] *= current;
						PivotRow[i] *= pivot;
					}
					pivot = PivotRow[c_pivot];
					current = CurrentRow[c_pivot];
					//Add or Subtract the pivot row FROM the current row depending on the signs of the pivot and current number.
					if ((pivot < zero && current < zero) || (pivot > zero && current > zero)) {
						l1:
						cout << "\t\tSubtracting pivot row from current row.\n";
						for (short int i = 0; i < columns; ++i) {
							CurrentRow[i] -= PivotRow[i];
						}
					}
					else {
						cout << "\t\tAdding pivot row to current row.\n";
						for (short int i = 0; i < columns; ++i) {
							CurrentRow[i] += PivotRow[i];
						}
					}
				}
				//Set the current row in the original equations matrix to be the new row.
				V[r_curr] = CurrentRow;
			}
			++r_curr;
			pivot = V[r_pivot][c_pivot];
			PivotRow = V[r_pivot];
		}
		++r_pivot;
		++c_pivot;
		r_curr = r_pivot + 1;
	}
	cout << "The triangulated matrix:\n";
	for (unsigned short i = 0; i < V.size(); ++i) {
		for (unsigned short j = 0; j < (V[i]).size(); ++j) {
			(V[i][j]).Print_Num(); cout << " ";
		}
		cout << "\n";
	}
	r_pivot = rows - 1;
	c_pivot = columns - 2;
	r_curr = r_pivot - 1;
	while (r_pivot >= 1) {
		pivot = V[r_pivot][c_pivot];
		PivotRow = V[r_pivot];
		while (r_curr >= 0) {
			current = V[r_curr][c_pivot];
			CurrentRow = V[r_curr];
			if (current != zero) {
				cout << "\tcurrent is not zero.\n";
				if (pivot == zero) {
					cout << "\t\tpivot is zero. Multiplying current row by pivot row.\n";
					//If pivot is zero, multiply the current row by the pivot row.
					for (short int i = 0; i < columns; ++i) {
						CurrentRow[i] *= PivotRow[i];
					}
				}
				else {
					cout << "\t\tpivot is not zero.\n";
					if (pivot == current) { cout << "\t\tpivot = current.\n"; goto l5; }
					//Find the lowest common multiple of the pivot and the current number.
					lcm = LCM(pivot, current);
					cout << "\t\tLCM = "; lcm.Print_Num(); cout << "\n";
					//Calculate the absolute values.
					pivot = abs(pivot);
					current = abs(current);
					cout << "\t\tabs(pivot) = "; pivot.Print_Num(); cout << ", abs(current) = "; current.Print_Num(); cout << "\n";
					//These are the numbers we'll multiply the pivot row and current row by.
					pivot = lcm / pivot;
					current = lcm / current;
					cout << "\t\tNumber to multiply pivot row by: "; pivot.Print_Num(); cout << "\n";
					cout << "\t\tNumber to multiply current row by: "; current.Print_Num(); cout << "\n";
					//Multiply the rows by the resulting numbers.
					for (short int i = 0; i < columns; ++i) {
						CurrentRow[i] *= current;
						PivotRow[i] *= pivot;
					}
					pivot = PivotRow[c_pivot];
					current = CurrentRow[c_pivot];
					//Add or Subtract the pivot row FROM the current row depending on the signs of the pivot and current number.
					if ((pivot < zero && current < zero) || (pivot > zero && current > zero)) {
					l5:
						cout << "\t\tSubtracting pivot row from current row.\n";
						for (short int i = 0; i < columns; ++i) {
							CurrentRow[i] -= PivotRow[i];
						}
					}
					else {
						cout << "\t\tAdding pivot row to current row.\n";
						for (short int i = 0; i < columns; ++i) {
							CurrentRow[i] += PivotRow[i];
						}
					}
				}
				//Set the current row in the original equations matrix to be the new row.
				V[r_curr] = CurrentRow;
			}
			--r_curr;
			pivot = V[r_pivot][c_pivot];
			PivotRow = V[r_pivot];
		}
		--r_pivot;
		--c_pivot;
		r_curr = r_pivot - 1;
	}
	cout << "The TWICE triangulated matrix:\n";
	for (short int i = 0; i < V.size(); ++i) {
		for (short int j = 0; j < (V[i]).size(); ++j) {
			(V[i][j]).Print_Num(); cout << " ";
		}
		cout << "\n";
	}
	//Part 3: row divisions to produce final result matrix.
	for (short int i = 0; i < V.size(); ++i) {
		V[i][columns - 1] /= V[i][i];
	}
}
#endif
