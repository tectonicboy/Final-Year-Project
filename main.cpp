#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include "bin_int.h"
#include "simult_solver.h"

typedef vector<bool> bvec;
typedef vector<bool>::iterator bvec_it;

using namespace std;

//Return type will be vector<vector<bin_int>>
vector<vector<bin_int>> Split(bin_int A, bin_int B, short k) {
	vector<bin_int> V, VA, VB, VC, VD, VE, VX;
	vector<vector<bin_int>> VZ;
	bin_int acc1(0), acc2(0), point(0), zero(0), G1(0), G2(0), Gpoint(0);
	string one1 = "1"; bin_int One1(one1);
	bool stop1 = false, stop2 = false;
	cout << "A.N.size = " << A.N.size() << ", k = " << k << "\n";
	double aux1 = BITSIZE, aux4;
	aux4 = aux1;
	aux4 /= k;
	short aux5 = ceil(aux4);
	cout << "AUX5 = " << aux5 << "\n";
	aux1 /= k;
	cout << "AUX1 = " << aux1 << "\n";
	short aux = ceil(aux1), num_pts = -1, counter = 1, aux2 = 0, aux3 = 0, pts;
	cout << "AUX = " << aux << "\n";
	aux1 = A.N.size();
	aux1 /= aux;
	cout << "AUX1 = " << aux1 << "\n";
	aux = ceil(aux1);
	cout << "AUX = " << aux << "\n";
	string s = "";
	bvec_it it1 = A.N.begin(), it2 = A.N.begin() + aux5;
	//VA is the vector containing the split first number A as separate bin_ints.
	while (!stop1) {
		if (stop2) { stop1 = true; }
		
		bvec vec(it1, it2);
		if (vec.size() > 0) {
			cout << "SPLIT VECTOR: ";
			for (bvec_size i = 0; i < vec.size(); ++i) {
				cout << vec[i];
			}
			cout << "\n";
			VA.push_back(bin_int(vec));
			++num_pts;
		}
		it1 = it2;
		while (counter <= aux5) {
			if (it2 != A.N.end()) {
				++it2;
			}
			else {
				stop2 = true;
				break;
			}
			++counter;
		}
		counter = 1;
	}
	num_pts = (num_pts * 2) - 1;
	cout << "CALCULATED NUMBER OF POINTS EXCLUDING ZERO AND INFINITY: " << num_pts << "\n";
	pts = num_pts;
	stop1 = false, stop2 = false;
	counter = 1;
	//VB is the vector containing the split second number B as separate bin_ints.
	it1 = B.N.begin(), it2 = B.N.begin() + aux5;
	while (!stop1) {
		if (stop2) { stop1 = true; }
		bvec vec(it1, it2);
		if (vec.size() > 0) {
			cout << "SPLIT VECTOR: ";
			for (bvec_size i = 0; i < vec.size(); ++i) {
				cout << vec[i];
			}
			cout << "\n";
			VB.push_back(bin_int(vec));
		}
		it1 = it2;
		while (counter <= aux5) {
			if (it2 != B.N.end()) {
				++it2;
			}
			else {
				stop2 = true;
				break;
			}
			++counter;
		}
		counter = 1;
	}
	reverse(VA.begin(), VA.end());
	reverse(VB.begin(), VB.end());
	cout << "The split number A is:\n";
	for (bvec_size i = 0; i < VA.size(); ++i) {
		cout << VA[i] << " ";
	}
	cout << "\nThe split number B is:\n";
	for (bvec_size i = 0; i < VB.size(); ++i) {
		cout << VB[i] << " ";
	}
	cout << "\n";
	counter = 1;
	if (num_pts > 0) {
		cout << "Please input " << num_pts << " points in binary. LSB is the leftmost bit.\n";
		//The vector of binary integers containing the points to evaluate at.
		while (counter <= (num_pts)) {
			cin >> s;
			V.push_back(bin_int(s));
			++counter;
		}
		cout << "The vector of evaluation points excluding zero and infinity:\n";
		for (bvec_size i = 0; i < V.size(); ++i) {
			V[i].Print_Num(); cout << " ";
		}
		cout << "\n";
	}
	//=============================================================================================
	VC.push_back(*(VA.end() - 1)), VD.push_back(*(VB.end() - 1));
	VC.push_back(*(VA.begin())), VD.push_back(*(VB.begin()));
	--pts;
	while (pts >= 0) {
		counter = aux - 2;
		point = V[pts];
		Gpoint = point;
		cout << "POINT: "; point.Print_Num(); cout << "\n";
		for (vector<bin_int>::size_type i = 0; i < VA.size(); ++i) {
			cout << "\t=========================================================================\n";
			cout << "\tTerms: VA[" << i << "] = " << VA[i] << ", VB[" << i << "] = " << VB[i] << "\n";
			if (!(i == VA.size() - 1)) {
				while (counter > i) {
					cout << "POINT TIMES POINT: ";
					Gpoint *= point;
					Gpoint.Print_Num(); cout << "\n";
					--counter;
				}
				counter = aux - 2;
				cout << "\tPoint to multiply terms by: " << Gpoint << "\n";

				G1 = VA[i] * Gpoint;
				G2 = VB[i] * Gpoint;
			}
			else {
				G1 = VA[i];
				G2 = VB[i];
			}
			cout << "\tResult: G1 = " << G1 << ", G2 = " << G2 << "\n";
			Gpoint = point;

			acc1 += G1;
			acc2 += G2;
			G1 = zero, G2 = zero;
		}
		cout << "\tEVALUATION: \n";
		cout << "\t\tC(p) = " << acc1; 
		cout << "\n\t\tD(p) = " << acc2 << "\n";
		cout << "\t=========================================================================\n";
		VC.push_back(acc1), VD.push_back(acc2);
		acc1 = zero, acc2 = zero;
		--pts;
	}
	cout << "The two evaluation vectors are:\n";
	cout << "The evaluation vector VC of As:\n";
	for (bvec_size i = 0; i < VC.size(); ++i) {
		cout << VC[i] << " ";
	}
	cout << "\nThe evaluation vector VD of Bs:\n";
	for (bvec_size i = 0; i < VD.size(); ++i) {
		cout << VD[i] << " ";
	}
	cout << "\n";
	//==============================================================================================
	//Multiply each entry C(p) by each entry D(p) to get evaluation values E(p).
	for (vector<bin_int>::size_type i = 0; i < VD.size(); ++i) {
		VE.push_back(VC[i] * VD[i]);
	}
	cout << "\nThe final evaluation vector VE:\n";
	for (bvec_size i = 0; i < VE.size(); ++i) {
		VE[i].Print_Num(); cout << " ";
	}
	cout << "\n";
	//==============================================================================================
	aux1 = (2 * aux) - 2;
	VX.push_back(One1);
	while (aux1 > 0) {
		VX.push_back(zero);
		--aux1;
	}
	VX.push_back(VE[0]);
	VZ.push_back(VX);
	VX = {};
	counter = num_pts;
	while (counter > 0) {
		point = V[counter - 1];
		cout << "POINT: "; point.Print_Num(); cout << "\n";
		Gpoint = point;
		aux1 = (2 * aux) - 2;
		aux2 = (2 * aux) - 3;
		while (aux1 > 0) {
			aux3 = aux2;
			while (aux3 > 0) {
				Gpoint *= point;
				--aux3;
			}
			--aux2;
			cout << "\tPoint to push pack: "; Gpoint.Print_Num(); cout << "\n";
			VX.push_back(Gpoint);
			Gpoint = point;
			--aux1;
		}
		VX.push_back(One1);
		cout << "\tLastly, pushing back VE[" << VE.size() - counter << "] = " << VE[VE.size() - counter] << "\n";
		VX.push_back(VE[VE.size() - counter]);
		VZ.push_back(VX);
		VX = {};
		--counter;
	}

	aux1 = (2 * aux) - 2;
	while (aux1 > 0) {
		VX.push_back(zero);
		--aux1;
	}
	VX.push_back(One1);
	VX.push_back(VE[1]);
	VZ.push_back(VX);

	cout << "The matrix of equations to be solved:\n";
	for (vector<bin_int>::size_type i = 0; i < VZ.size(); ++i) {
		for (vector<bin_int>::size_type j = 0; j < VZ[i].size(); ++j) {
			cout << VZ[i][j] << " ";
		}
		cout << "\n";
	}
	return VZ;
}

int main(void) {
	
	cout << "TESTING SPLITTING FUNCTION.\n";
	string s1 = "1100001010000100", 
		   s2 = "0100001100001100";
	bin_int N1(s1), N2(s2);
	vector<vector<bin_int>> V_solve;
	V_solve = Split(N1, N2, 4);
	Solve(V_solve);

	
	
	/*
	char c = '0';
	int j = 0;
	while (j == 0) {
		cout << "\t\t**** TESTING INITIATED ****\nEnter 0 to quit, 1 to test LCM, 2 to test simultaneous solver.\n";
		cin >> c;
		if (c == '0') {
			return 0;
		}
		else if (c == '1') {
			string s1, s2;
			cout << "\nPlease input the two binary numbers (one per line) to find the LCM of.\n";
			cin >> s1 >> s2;
			bin_int n1(s1), n2(s2), n3 = LCM(n1, n2);
			cout << "LCM = "; n3.Print_Num(); cout << "\n";
		}
		else if (c == '2') {
			int n = 0;
			vector<vector<bin_int>> V;
			vector<bin_int>vec;
			string s = "";
			cout << "Please input the number of equations in the system.\n";
			cin >> n;
			const int m = n + 1;
			int m_m = m;
			while (n > 0) {
				cout << "Please input a list of " << m << " " << BITSIZE << "-bit numbers.\n";
				while (m_m > 0) {
					cin >> s;
					bin_int *numptr = new bin_int(s);
					vec.push_back(*numptr);
					delete numptr;
					--m_m;
				}
				m_m = m;
				V.push_back(vec);
				vec = {};
				--n;
			}
			cout << "Ready to input the matrix:\n";
			for (unsigned short i = 0; i < V.size(); ++i) {
				for (unsigned short j = 0; j < (V[i]).size(); ++j) {
					(V[i][j]).Print_Num(); cout << " ";
				}
				cout << "\n";
			}
			Solve(V);
			cout << "The solution matrix:\n";
			for (unsigned short i = 0; i < V.size(); ++i) {
				for (unsigned short j = 0; j < (V[i]).size(); ++j) {
				(V[i][j]).Print_Num(); cout << " ";
				}
				cout << "\n";
			}
		}
	}
	*/

	/*
	//13
	string thirteen = "1011000000000000";
	//-13
	string minusthirteen = "1100111111111111";
	//4
	string four = "0010000000000000";
	//-4
	string minusfour = "0011111111111111";
	//91
	string ninetyone = "1101101000000000";
	//-91
	string minusninetyone = "1010010111111111";
	//7
	string seven = "1110000000000000";
	//-7
	string minusseven = "1001111111111111";
	//0
	string zero = "0000000000000000";
	//1
	string one = "1000000000000000";
	//-1
	string minusone = "1111111111111111";
	//17
	string seventeen = "1000100000000000";
	//-17
	string minusseventeen = "1111011111111111";
	//2
	string two = "0100000000000000";
	//-2
	string minustwo = "0111111111111111";
	//6
	string six = "0110000000000000";
	//-6
	string minussix = "0101111111111111";
	//3
	string three = "1100000000000000";
	//-3
	string minusthree = "1011111111111111";
	//5
	string five = "1010000000000000";
	//-5
	string minusfive = "1101111111111111";
	bin_int Thirteen(thirteen),
		MinusThirteen(minusthirteen),
		Four(four),
		MinusFour(minusfour),
		NinetyOne(ninetyone),
		MinusNinetyOne(minusninetyone),
		Seven(seven),
		MinusSeven(minusseven),
		Zero(zero),
		One(one),
		MinusOne(minusone),
		Seventeen(seventeen),
		MinusSeventeen(minusseventeen),
		Two(two),
		MinusTwo(minustwo),
		Three(three),
		MinusThree(minusthree),
		Five(five),
		MinusFive(minusfive),
		Six(six),
		MinusSix(minussix);

	cout << "The number Six was constructed as: " << Six << "\n";
	string test1 = "0010000110101000";
	string test2 = "1000011000101100";
	bin_int Test1(test1);
	bin_int Test2(test2);
	bool b;
	bin_int Result = Test1 * Test2;
	cout << Result << "\n";
	Result = Test1 + Test2;
	cout << Result << "\n";
	Result = Test2 + Test1;
	cout << Result << "\n";
	Result = Test2 - Test1;
	cout << Result << "\n";
	Result = Test1 - Test2;
	*/

	return 0;
}
