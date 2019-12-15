#include <iostream>
#include <vector>

#include "bin_int.h"
#include "simult_solver.h"

using namespace std;

int main(void) {
	char c = '0';
	int j = 0;
	/*while (j == 0) {
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
			for (auto i = 0; i < V.size(); ++i) {
				for (auto j = 0; j < (V[i]).size(); ++j) {
					(V[i][j]).Print_Num(); cout << " ";
				}
				cout << "\n";
			}
			Solve(V, 4, 5);
			cout << "The solution matrix:\n";
			for (auto i = 0; i < V.size(); ++i) {
				for (auto j = 0; j < (V[i]).size(); ++j) {
					(V[i][j]).Print_Num(); cout << " ";
				}
				cout << "\n";
			}
		}
	}*/
	
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
	string test1 = "0001111000000000";
	string test2 = "0101000000000000";
	bin_int Test1(test1), Test2(test2);

	bin_int Result = Test1 / Test2;

	Result.Print_Num(); cout << "\n";
	
	return 0;
}
