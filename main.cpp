#include <iostream>
#include <vector>
#include "functions.h"

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

	double M[32][32];

	int r, c, d1 = 0, d2 = 0;
	double d3;
	cin >> r >> c;
	//Make up a system of equations (populating the augmented matrix)
	while (d1 < r) {
		while (cin >> d3) {
			M[d1][d2] = d3;
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
			cout << M[F][D] << " ";
		}
		cout << "\n";
	}


	int r_curr = 1, c_pivot = 0, r_pivot = 0;
	double aux;

	while (c_pivot < c-1) {
		cout << "PIVOT column: " << c_pivot << ", PIVOT = " << M[r_pivot][c_pivot] << "\n";
		while (r_curr <= r-1) {
			aux = (M[r_curr][c_pivot] / M[r_pivot][c_pivot]) * (-1);
			cout << "\t COMPUTED AUX = " << aux << "\n";
			for (int F = 0; F < c; ++F) {
				cout << "\t\t COMPUTING: M[" << r_curr << "][" << F << "] => " << aux << " * " << M[r_pivot][F] << " = " 
					<< aux * M[r_pivot][F] << "\n";
				M[r_curr][F] += aux * M[r_pivot][F];
			}
			++r_curr;
			cout << "Changed matrix to: \n";
			//print matrix
			for (int F = 0; F < r; ++F) {
				for (int D = 0; D < c; ++D) {
					cout << M[F][D] << " ";
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
			cout << M[F][D] << " ";
		}
		cout << "\n";
	}


	r_pivot = r-1, c_pivot = c - 2, r_curr = r_pivot - 1;
	while (c_pivot > 0) {
		cout << "PIVOT column: " << c_pivot << ", PIVOT = " << M[r_pivot][c_pivot] << "\n";
		while (r_curr >= 0) {
			aux = (M[r_curr][c_pivot] / M[r_pivot][c_pivot]) * (-1);
			cout << "\t COMPUTED AUX = " << aux << "\n";
			for (int F = 0; F < c; ++F) {
				M[r_curr][F] += aux * M[r_pivot][F];
			}
			--r_curr;
			cout << "Changed matrix to: \n";
			//print matrix
			for (int F = 0; F < r; ++F) {
				for (int D = 0; D < c; ++D) {
					cout << M[F][D] << " ";
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
			cout << M[F][D] << " ";
		}
		cout << "\n";
	}

	for (int F = 0; F < r; ++F) {
		M[F][c - 1] /= M[F][F];
		M[F][F] = 1;
	}

	cout << "The solution matrix:\n";
	//print matrix
	for (int F = 0; F < r; ++F) {
		for (int D = 0; D < c; ++D) {
			cout << M[F][D] << " ";
		}
		cout << "\n";
	}
	string s1 = "11101111", s2 = "11111111";
	bin_num N1(s1), N2(s2), N3 = N1 + N2, N4 = N1 * N2, N5 = N2 - N1, N6 = N1 - N2;
	cout << "\n***********************************************\n";
	N1.Print_Num();
	cout << "\tProperties of N1: MSB = " << N1.MSB << ", LSB = " << N1.LSB << ", size = " << N1.size << "\n";
	N2.Print_Num();
	cout << "\tProperties of N2: MSB = " << N2.MSB << ", LSB = " << N2.LSB << ", size = " << N2.size << "\n";
	N3.Print_Num();
	cout << "\tProperties of N1 + N2: MSB = " << N3.MSB << ", LSB = " << N3.LSB << ", size = " << N3.size << "\n";
	N4.Print_Num();
	cout << "\tProperties of N1 * N2: MSB = " << N4.MSB << ", LSB = " << N4.LSB << ", size = " << N4.size << "\n";
	N5.Print_Num();
	cout << "\tProperties of N2 - N1: MSB = " << N5.MSB << ", LSB = " << N5.LSB << ", size = " << N5.size << "\n";
	N6.Print_Num();
	cout << "\tProperties of N1 - N2: MSB = " << N6.MSB << ", LSB = " << N6.LSB << ", size = " << N6.size << "\n";
	return 0;
}
