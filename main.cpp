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
void Split(bin_int A, bin_int B, short k) {
	vector<bin_int> V, VA, VB, VC, VD, VE;
	bin_int acc1(0), acc2(0), point(0), zero(0), G1(0), G2(0), Gpoint(0);
	bool stop1 = false;
	cout << "A.N.size = " << A.N.size() << ", k = " << k << "\n";
	double aux1 = A.N.size();
	aux1 /= k;
	cout << "aux1 = " << aux1 << "\n";
	short aux = ceil(aux1), num_pts = (aux * 2) - 3, counter = 1;
	cout << "AUX = " << aux << "\n";
	string s = "";
	if (num_pts > 0) {
		cout << "Please input " << num_pts << " points in binary. LSB is the leftmost bit.\n";
		//The vector of binary integers containing the points to evaluate at.
		//ADD FUNCTIONALITY FOR ZERO AND INFINITY WHICH WILL ALWAYS BE CHOSEN??
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
	counter = 1;
	bvec_it it1 = A.N.begin(), it2 = A.N.begin() + aux;
	//VA is the vector containing the split first number A as separate bin_ints.
	while (!stop1) {
		bvec vec(it1, it2);
		VA.push_back(bin_int(vec));
		it1 = it2;
		while (counter <= aux) {
			if (it2 != A.N.end()) {
				++it2;
			}
			else {
				stop1 = true;
				break;
			}
			++counter;
		}
		counter = 1;
	}
	stop1 = false;
	counter = 1;
	//VB is the vector containing the split second number B as separate bin_ints.
	it1 = B.N.begin(), it2 = B.N.begin() + aux;
	while (!stop1) {
		bvec vec(it1, it2);
		VB.push_back(bin_int(vec));
		it1 = it2;
		while (counter <= aux) {
			if (it2 != B.N.end()) {
				++it2;
			}
			else {
				stop1 = true;
				break;
			}
			++counter;
		}
		counter = 1;
	}
	cout << "The split number A is:\n";
	for (bvec_size i = 0; i < VA.size(); ++i) {
		VA[i].Print_Num(); cout << " ";
	}
	cout << "\nThe split number B is:\n";
	for (bvec_size i = 0; i < VB.size(); ++i) {
		VB[i].Print_Num(); cout << " ";
	}
	cout << "\n";
	//=============================================================================================
	VC.push_back(*(VA.end() - 1)), VD.push_back(*(VB.end() - 1));
	VC.push_back(*(VA.begin())), VD.push_back(*(VB.begin()));
	--num_pts;
	while (num_pts >= 0) {
		counter = aux - 2;
		point = V[num_pts];
		Gpoint = point;
		cout << "POINT: "; point.Print_Num(); cout << "\n";
		for (vector<bin_int>::size_type i = 0; i < VA.size(); ++i) {
			cout << "\t=========================================================================\n";
			while (counter > i) {
				cout << "POINT TIMES POINT!\n";
				Gpoint *= point;
				--counter;
			}
			counter = aux - 2;
			cout << "\tTerms: VA[i] = "; VA[i].Print_Num(); cout << ", VB[i] = "; VB[i].Print_Num(); cout << "\n";
			cout << "\tPoint to multiply terms by: "; Gpoint.Print_Num(); cout << "\n";
			cout << "\t=========================================================================\n";
			G1 = VA[i] * Gpoint;
			G2 = VB[i] * Gpoint;
			
			acc1 += VA[i];
			acc2 += VB[i];
		}
		acc1 = zero, acc2 = zero;
		VC.push_back(acc1), VD.push_back(acc2);
		--num_pts;
	}
	cout << "The two evaluation vectors are:\n";
	cout << "The evaluation vector VC of As:\n";
	for (bvec_size i = 0; i < VC.size(); ++i) {
		VC[i].Print_Num(); cout << " ";
	}
	cout << "\nThe evaluation vector VD of Bs:\n";
	for (bvec_size i = 0; i < VD.size(); ++i) {
		VD[i].Print_Num(); cout << " ";
	}
	cout << "\n";
	//==============================================================================================
	for (vector<bin_int>::size_type i = 0; i < VD.size(); ++i) {
		VE.push_back(VC[i] * VD[i]);
	}
	cout << "\nThe final evaluation vector VE:\n";
	for (bvec_size i = 0; i < VE.size(); ++i) {
		VE[i].Print_Num(); cout << " ";
	}
	cout << "\n";
}



int main(void) {
	
	cout << "TESTING SPLITTING FUNCTION.\n";
	string s1 = "1001111100010101", s2 = "0001010111110001";
	bin_int N1(s1), N2(s2);
	Split(N1, N2, 4);
	


	/*char c = '0';
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
	}*/


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

	string test1 = "0000100000000000";
	string test2 = "0101000000000000";
	bin_int Test1(test1);
	bin_int Test2(test2);

	bin_int Result = Test1 + Test2;

	Result.Print_Num(); cout << "\n";
	
	*/

	return 0;
}
