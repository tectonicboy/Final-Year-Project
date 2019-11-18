#include <iostream>
#include <vector>
#include "bin_int.h"

using namespace std;



int main() {
	/*short int k = 0, n = 0, m = 0, i = 0, j = 0, point;
	cout << "Please input values for n, m and k, where:\n";
	cout << "k is for splitting, n is size of bit vectors, m is the number of bit vectors we'll multiply.\n";
	cin >> n >> m >> k;
	short int num_pts = (2 * (n / k)) - 1;
	//Points to evaluate at.
	short int P[64];
	cout << "Please input the points to evaluate at. We need " << num_pts << " points in total.\n";
	cout << "We always evaluate at 0 and infinity, so input " << num_pts - 2 << " more points.\n";
	while (cin >> point) {
		P[i] = point;
		++i;
		if (i == num_pts - 2) { break; }
	}
	i = 0;
	//The binary numbers we'll multiply.
	bool bvecs[64][8];
	bool b = 0;
	while (j != m) {
		cout << "Awaiting input of next " << n <<  "-bit binary number. So far we have " << j << " numbers out of " << m << ".\n";
		while (cin >> b) {
			bvecs[i][j] = b;
			++i;
			if (i == n) { break; }
		}
		i = 0;
		++j;
	}
	cout << "End of parameter input.\n";
	*/

	//*************************** SOLVING THE SIMULTANEOUS EQUATIONS ********************************

	double V[32][32];

	int r, c, d1 = 0, d2 = 0;
	double d3;
	cin >> r >> c;
	//Make up a system of equations (populating the augmented matrix)
	while (d1 < r) {
		while (cin >> d3) {
			V[d1][d2] = d3;
			++d2;
			if (d2 >= c) { goto label; }
		}
	label:
		++d1;
		d2 = 0;
	}
	cout << "\n\nINITIAL PARAMETERS: \n";
	cout << "r = " << r << "\nc = " << c << "\n\n";
	cout << "AUGMENTED MATRIX:\n";
	//print matrix
	for (int F = 0; F < r; ++F) {
		for (int D = 0; D < c; ++D) {
			cout << V[F][D] << " ";
		}
		cout << "\n";
	}


	int r_curr = 1, c_pivot = 0, r_pivot = 0;
	double aux;

	while (c_pivot < c-1) {
		cout << "PIVOT column: " << c_pivot << ", PIVOT = " << V[r_pivot][c_pivot] << "\n";
		while (r_curr <= r-1) {
			aux = (V[r_curr][c_pivot] / V[r_pivot][c_pivot]) * (-1);
			cout << "\t COMPUTED AUX = " << aux << "\n";
			for (int F = 0; F < c; ++F) {
				cout << "\t\t COMPUTING: M[" << r_curr << "][" << F << "] => " << aux << " * " << V[r_pivot][F] << " = " 
					<< aux * V[r_pivot][F] << "\n";
				V[r_curr][F] += aux * V[r_pivot][F];
			}
			++r_curr;
			cout << "Changed matrix to: \n";
			//print matrix
			for (int F = 0; F < r; ++F) {
				for (int D = 0; D < c; ++D) {
					cout << V[F][D] << " ";
				}
				cout << "\n";
			}
		}

		++c_pivot;
		++r_pivot;
		r_curr = r_pivot + 1;
	}

	//after operation set 1
	cout << "In triangular form now:\n";
	//print matrix
	for (int F = 0; F < r; ++F) {
		for (int D = 0; D < c; ++D) {
			cout << V[F][D] << " ";
		}
		cout << "\n";
	}


	r_pivot = r-1, c_pivot = c - 2, r_curr = r_pivot - 1;
	while (c_pivot > 0) {
		cout << "PIVOT column: " << c_pivot << ", PIVOT = " << V[r_pivot][c_pivot] << "\n";
		while (r_curr >= 0) {
			aux = (V[r_curr][c_pivot] / V[r_pivot][c_pivot]) * (-1);
			cout << "\t COMPUTED AUX = " << aux << "\n";
			for (int F = 0; F < c; ++F) {
				V[r_curr][F] += aux * V[r_pivot][F];
			}
			--r_curr;
			cout << "Changed matrix to: \n";
			//print matrix
			for (int F = 0; F < r; ++F) {
				for (int D = 0; D < c; ++D) {
					cout << V[F][D] << " ";
				}
				cout << "\n";
			}
		}
		--c_pivot;
		--r_pivot;
		r_curr = r_pivot - 1;
	}

	//after second reduction
	cout << "After 2nd set of reduction row operations:\n";
	//print matrix
	for (int F = 0; F < r; ++F) {
		for (int D = 0; D < c; ++D) {
			cout << V[F][D] << " ";
		}
		cout << "\n";
	}

	for (int F = 0; F < r; ++F) {
		V[F][c - 1] /= V[F][F];
		V[F][F] = 1;
	}

	cout << "The solution matrix:\n";
	//print matrix
	for (int F = 0; F < r; ++F) {
		for (int D = 0; D < c; ++D) {
			cout << V[F][D] << " ";
		}
		cout << "\n";
	}


	string Sx = "0011000", Sy = "1010001", Sz = "1111111";
	bin_int Nx(Sx), Ny(Sy), Nz(Sz);

	cout << "\n\n\n \t\t************TESTING BIN_INT***************\n\n\n";

	cout << "Ex. one: 12 - 69 = Nx - Ny.\n"; Nx.Print_Num(); cout << "\n-\n"; Ny.Print_Num(); cout << "\n----------\n";
	bin_int N11 = Nx - Ny;
	N11.Print_Num(); cout << "\n";

	cout << "\n\n";

	cout << "Ex. two: 127 - 69 = Nz - Ny.\n"; Nz.Print_Num(); cout << "\n-\n"; Ny.Print_Num(); cout << "\n----------\n";
	bin_int N12 = Nz - Ny;
	N12.Print_Num(); cout << "\n";

	cout << "\n\n";

	cout << "Ex. three: 69 - 69 = Ny - Ny.\n"; Ny.Print_Num(); cout << "\n-\n"; Ny.Print_Num(); cout << "\n----------\n";
	bin_int N13 = Ny - Ny;
	N13.Print_Num(); cout << "\n";

	cout << "\n\n";

	cout << "Ex. four: 127 - 12 = Nz - Nx.\n"; Nz.Print_Num(); cout << "\n-\n"; Nx.Print_Num(); cout << "\n----------\n";
	bin_int N14 = Nz - Nx;
	N14.Print_Num(); cout << "\n";

	cout << "\n\n";

	cout << "Ex. five: 12 - 127 = Nz - Ny.\n"; Nx.Print_Num(); cout << "\n-\n"; Nz.Print_Num(); cout << "\n----------\n";
	bin_int N15 = Nx - Nz;
	N15.Print_Num(); cout << "\n";

	return 0;
}
