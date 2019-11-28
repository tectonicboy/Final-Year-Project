#include <iostream>
#include <vector>
#include "bin_int.h"
#include "simult_solver.h"

using namespace std;

int main() {

	string Sx = "1111000000000000", Sy = "1000111111111111";
	bin_int Nx(Sx), Ny(Sy); 
	bin_int N1 = Nx + Ny, N2 = Nx * Nx, N3 = Nx - Ny;

	cout << "\n\n\n \t\t************TESTING BIN_INT***************\n\n\n";
	cout << "15 + (-15) = "; N1.Print_Num(); cout << "\n";
	cout << "\tAfter addition, Nx = "; Nx.Print_Num(); cout << ", Ny = "; Ny.Print_Num(); cout << "\n";
	cout << "15 * 15 = "; N2.Print_Num(); cout << "\n";
	cout << "\tAfter multiplication, Nx = "; Nx.Print_Num(); cout << ", Ny = "; Ny.Print_Num(); cout << "\n";
	cout << "15 - (-15) = "; N3.Print_Num(); cout << "\n";
	cout << "\tAfter subtraction, Nx = "; Nx.Print_Num(); cout << ", Ny = "; Ny.Print_Num(); cout << "\n";

	cout << "\n\n*********** TESTING COMPARISON OPERATORS *************\n\n";
	cout << "15 > (-15): " << (Nx > Ny) << ", Expected 1\n";
	cout << "15 < (-15): " << (Nx < Ny) << ", Expected 0\n";
	Ny.Negate();
	cout << "Negated -15: "; Ny.Print_Num(); cout << "\n";
	cout << "15 == (-(-15)): " << (Nx == Ny) << ", Expected 1\n";
	cout << "15 <= (-(-15)): " << (Nx <= Ny) << ", Expected 1\n";
	cout << "15 >= (-(-15)): " << (Nx >= Ny) << ", Expected 1\n";
	cout << "15 != (-(-15)): " << (Nx != Ny) << ", Expected 0\n";
	cout << "15 < (-(-15)): " << (Nx < Ny) << ", Expected 0\n";
	cout << "15 > (-(-15)): " << (Nx > Ny) << ", Expected 0\n";
	cout << "15 != 15: " << (Nx != Nx) << ", Expected 0\n";
	Ny.Negate();
	cout << "Negated it again: "; Ny.Print_Num(); cout << "\n";
	cout << "15 == (-15): " << (Nx == Ny) << ", Expected 0\n";
	cout << "15 != (-15): " << (Nx != Ny) << ", Expected 1\n";

	cout << "Testing increment and decrement operators.\n";

	cout << "++15 = "; ++Nx; Nx.Print_Num(); cout << "\n";
	cout << "++ (-15) = "; ++Ny; Ny.Print_Num(); cout << "\n";
	cout << "--16 = "; --Nx; Nx.Print_Num(); cout << "\n";
	cout << "-- (-14) = "; --Ny; Ny.Print_Num(); cout << "\n";




	cout << "\t\t*******TESTING LCM TEMPLATE FUNCTION WITH BINARY LIBRARY*******\n\n";
	//43 and 210 in 16-bit 
	string ss1 = "1101010000000000", ss2 = "0100101100000000";
	bin_int f1(ss1), f2(ss2), f3 = LCM(f1, f2);
	cout << "The Lowest Common Multiple is: "; f3.Print_Num(); cout << "\n";

	/*cout << "\t\t**********TESTING SOMULTANEOUS SOLVER WITH INTS*************\n\n";
	vector<int>V1 = { 2, 1, -1, 8 };
	vector<int>V2 = { -3, -1, 2, -11 };
	vector<int>V3 = { -2, 1, 2, -3 };
	int ii1 = 3, ii2 = 4;
	vector<vector<int>>V = { V1, V2, V3 };
	Solve(V, ii1, ii2);
	cout << "Solutions: " << V[0][3] << ", " << V[1][3] << ", " << V[2][3] << "\n";
	*/
	return 0;
}
