#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>
#include <string>

typedef vector<bool> bvec;
typedef vector<bool>::iterator bvec_it;

using namespace std;

//The template function to find the LCM of two numbers, implementing Euclid's Algorithm.
template <typename T>
T LCM(T& a, T& b) {
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
	//cout << "max = " << r0 << ", min = " << r1 << "\n";
	bool wasE = false;
	vector<T> V;
	int x = 0;
	while (x == 0) {
		aux = r0 - r1;
		V.push_back(aux);
		if (wasE) {
			//cout << "\tIt was E.\n";
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
	//cout << "EXITED LCM LOOP!\n";
	T c = abs(a);
	//cout << "First abs done.\n";
	T d = abs(b);
	//cout << "Second abs done.\n";
	lcm = c / gcd;
//	cout << "Division abs(a) / GCD is done.\n";
	lcm *= d;
	//cout << "Multiplication LCM *= abs(b) is done.\n";
	if (b1) { a.Negate(); }
	if (b2) { b.Negate(); }
	return lcm;
}


//The template for solving a system of linear simultaneous equations by Gaussian elimination.
template <typename T>
void Solve(vector<vector<T>>& V) {
	int rows = V.size(), columns = V[0].size(), r_curr = 1, r_pivot = 0, c_pivot = 0;
	T pivot = V[0][0], current = V[0][1], lcm(0), zero(0);
	bool b1 = false;
	vector<T> PivotRow, CurrentRow;
	//First triangulation loop.
	while (r_pivot <= rows - 2) {
		pivot = V[r_pivot][c_pivot];
		PivotRow = V[r_pivot];
		//cout << "PivotRow = " << r_pivot << ", pivot = " << pivot << "\n";
		//What happens at each row.
		while (r_curr <= rows - 1) {
			while (!b1) {
				for (auto i = V[r_curr].begin(); i != V[r_curr].end(); ++i) {
					if ((*i).N[0]) {
						b1 = true;
					}
				}
				if (!b1) {
			//		cout << "Shifting current row...\n";
					for (auto i = V[r_curr].begin(); i != V[r_curr].end(); ++i) {
						(*i).operator<<(1);
					}
				}
			}
			b1 = false;
			current = V[r_curr][c_pivot];
			CurrentRow = V[r_curr];
			//cout << "\tCurrent row = " << r_curr << "\n";
			//cout << "\tcurrent = " << current << "\n";
			if (current != zero) {
			//	cout << "\tcurrent is not zero.\n";
				if (pivot == zero) {
				//	cout << "\t\tpivot is zero. Multiplying current row by pivot row.\n";
					//If pivot is zero, multiply the current row by the pivot row.
					for (size_t i = 0; i < columns; ++i) {
						CurrentRow[i] *= PivotRow[i];
					}
				}
				else {
					//cout << "\t\tpivot is not zero.\n";
					if (pivot == current) {/* cout << "\t\tpivot = current.\n";*/ goto l1; }
					//Find the lowest common multiple of the pivot and the current number.
					lcm = LCM(pivot, current);
					//cout << "\t\tLCM = " << lcm << "\n";
					//Calculate the absolute values.
					pivot = abs(pivot);
					current = abs(current);
					//cout << "\t\tabs(pivot) = " << pivot << ", abs(current) = " << current << "\n";
					//These are the numbers we'll multiply the pivot row and current row by.
					pivot = lcm / pivot;
					current = lcm / current;
					//cout << "\t\tNumber to multiply pivot row by: " << pivot << "\n";
					//cout << "\t\tNumber to multiply current row by: " << current << "\n";
					//Multiply the rows by the resulting numbers.
					for (size_t i = 0; i < columns; ++i) {
						CurrentRow[i] *= current;
						PivotRow[i] *= pivot;
					}
					pivot = PivotRow[c_pivot];
					current = CurrentRow[c_pivot];
					//Add or Subtract the pivot row FROM the current row depending on the signs of the pivot and current number.
					if ((pivot < zero && current < zero) || (pivot > zero&& current > zero)) {
					l1:
					//	cout << "\t\tSubtracting pivot row from current row.\n";
						for (size_t i = 0; i < columns; ++i) {
							CurrentRow[i] -= PivotRow[i];
						}
					}
					else {
					//	cout << "\t\tAdding pivot row to current row.\n";
						for (size_t i = 0; i < columns; ++i) {
							CurrentRow[i] += PivotRow[i];
						}
					}
				}
				//Set the current row in the original equations matrix to be the new row.
				V[r_curr] = CurrentRow;
				while (!b1) {
					for (auto i = V[r_curr].begin(); i != V[r_curr].end(); ++i) {
						if ((*i).N[0]) {
							b1 = true;
						}
					}
					if (!b1) {
					//	cout << "Shifting current row...\n";
						for (auto i = V[r_curr].begin(); i != V[r_curr].end(); ++i) {
							(*i).operator<<(1);
						}
					}
				}
				b1 = false;
				//for (unsigned short i = 0; i < V.size(); ++i) {
				//	for (unsigned short j = 0; j < (V[i]).size(); ++j) {
				//		cout << V[i][j] << " ";
				//	}
				//	cout << "\n";
				//}
			}
			++r_curr;
			pivot = V[r_pivot][c_pivot];
			PivotRow = V[r_pivot];
		}
		++r_pivot;
		++c_pivot;
		r_curr = r_pivot + 1;
	}
	/*cout << "The triangulated matrix:\n";
	for (size_t i = 0; i < V.size(); ++i) {
		for (size_t j = 0; j < (V[i]).size(); ++j) {
			cout << V[i][j] << " ";
		}
		cout << "\n";
	}*/
	r_pivot = rows - 1;
	c_pivot = columns - 2;
	r_curr = r_pivot - 1;
	while (r_pivot >= 1) {
		while (!b1) {
			for (auto i = V[r_curr].begin(); i != V[r_curr].end(); ++i) {
				if ((*i).N[0]) {
					b1 = true;
				}
			}
			if (!b1) {
			//	cout << "Shifting current row...\n";
				for (auto i = V[r_curr].begin(); i != V[r_curr].end(); ++i) {
					(*i).operator<<(1);
				}
			}
		}
		b1 = false;
		pivot = V[r_pivot][c_pivot];
		PivotRow = V[r_pivot];
		//cout << "PivotRow = " << r_pivot << ", pivot = " << pivot << "\n";
		while (r_curr >= 0) {
			current = V[r_curr][c_pivot];
			CurrentRow = V[r_curr];
			//cout << "\tCurrent row = " << r_curr << "\n";
			//cout << "\tcurrent = " << current << "\n";
			if (current != zero) {
				//cout << "\tcurrent is not zero.\n";
				if (pivot == zero) {
					//cout << "\t\tpivot is zero. Multiplying current row by pivot row.\n";
					//If pivot is zero, multiply the current row by the pivot row.
					for (size_t i = 0; i < columns; ++i) {
						CurrentRow[i] *= PivotRow[i];
					}
				}
				else {
					//cout << "\t\tpivot is not zero.\n";
					if (pivot == current) { /*cout << "\t\tpivot = current.\n"; */goto l5; }
					//Find the lowest common multiple of the pivot and the current number.
					lcm = LCM(pivot, current);
					//cout << "\t\tLCM = " << lcm << "\n";
					//Calculate the absolute values.
					pivot = abs(pivot);
					current = abs(current);
					//cout << "\t\tabs(pivot) = " << pivot << ", abs(current) = " << current << "\n";
					//These are the numbers we'll multiply the pivot row and current row by.
					pivot = lcm / pivot;
					current = lcm / current;
					//cout << "\t\tNumber to multiply pivot row by: " << pivot << "\n";
					//cout << "\t\tNumber to multiply current row by: " << current << "\n";
					//Multiply the rows by the resulting numbers.
					for (size_t i = 0; i < columns; ++i) {
						CurrentRow[i] *= current;
						PivotRow[i] *= pivot;
					}
					pivot = PivotRow[c_pivot];
					current = CurrentRow[c_pivot];
					//Add or Subtract the pivot row FROM the current row depending on the signs of the pivot and current number.
					if ((pivot < zero && current < zero) || (pivot > zero&& current > zero)) {
					l5:
					//	cout << "\t\tSubtracting pivot row from current row.\n";
						for (size_t i = 0; i < columns; ++i) {
							CurrentRow[i] -= PivotRow[i];
						}
					}
					else {
					//	cout << "\t\tAdding pivot row to current row.\n";
						for (size_t i = 0; i < columns; ++i) {
							CurrentRow[i] += PivotRow[i];
						}
					}
				}
				//Set the current row in the original equations matrix to be the new row.
				V[r_curr] = CurrentRow;
				while (!b1) {
					for (auto i = V[r_curr].begin(); i != V[r_curr].end(); ++i) {
						if ((*i).N[0]) {
							b1 = true;
						}
					}
					if (!b1) {
					//	cout << "Shifting current row...\n";
						for (auto i = V[r_curr].begin(); i != V[r_curr].end(); ++i) {
							(*i).operator<<(1);
						}
					}
				}
				b1 = false;
				//for (unsigned short i = 0; i < V.size(); ++i) {
				//	for (unsigned short j = 0; j < (V[i]).size(); ++j) {
				////		cout << V[i][j] << " ";
				//	}
				//	cout << "\n";
				//}
			}
			--r_curr;
			pivot = V[r_pivot][c_pivot];
			PivotRow = V[r_pivot];
		}
		--r_pivot;
		--c_pivot;
		r_curr = r_pivot - 1;
	}
	/*cout << "The TWICE triangulated matrix:\n";
	for (unsigned short i = 0; i < V.size(); ++i) {
		for (unsigned short j = 0; j < (V[i]).size(); ++j) {
			cout << V[i][j] << " ";
		}
		cout << "\n";
	}*/
	//Part 3: row divisions to produce final result matrix.
	for (unsigned short i = 0; i < V.size(); ++i) {
		V[i][columns - 1] /= V[i][i];
		V[i][i] /= V[i][i];
	}
	/*cout << "The result matrix:\n";
	for (unsigned short i = 0; i < V.size(); ++i) {
		for (unsigned short j = 0; j < (V[i]).size(); ++j) {
			cout << V[i][j] << " ";
		}
		cout << "\n";
	}*/
}

//The function implementing Toom-Cook multiplication on binary numbers.
bvec ToomCook(bin_int A, bin_int B, short k) {
	vector<bin_int> V, VA, VB, VC, VD, VE, VX;
	vector<vector<bin_int>> VZ;
	bin_int zero(0);

	bvec_size old_size = BITSIZE;
	bvec_size new_size = old_size + 6;

	if (A == zero || B == zero) {
		while (zero.N.size() < (BITSIZE * 2) + 1) {
			zero.N.push_back(false);
		}
	//	cout << zero << "\n";
		return zero.N;
	}

	BITSIZE = new_size;

	while (zero.N.size() < new_size) {
		zero.N.push_back(false);
	}
	bin_int acc1(0), acc2(0), point(0), G1(0), G2(0), Gpoint(0);
	string one1 = "1"; bin_int One1(one1);
	bool stop1 = false, stop2 = false, neg = false;

	//cout << "A.N.size = " << A.N.size() << ", k = " << k << "\n";
	double aux1 = old_size, aux4;
	aux4 = aux1;
	aux4 /= k;
	short aux5 = ceil(aux4);
	//cout << "AUX5 = " << aux5 << "\n";
	aux1 /= k;
	//cout << "AUX1 = " << aux1 << "\n";
	short aux = ceil(aux1), num_pts = -1, counter = 1, aux2 = 0, aux3 = 0, pts;
	//cout << "AUX = " << aux << "\n";
	aux1 = A.N.size();
	aux1 /= aux;
	//cout << "AUX1 = " << aux1 << "\n";
	aux = ceil(aux1);
	//cout << "AUX = " << aux << "\n";
	string s = "";
	bvec_it it1 = A.N.begin(), it2 = A.N.begin() + aux5;
	//VA is the vector containing the split first number A as separate bin_ints.
	while (!stop1) {
		if (stop2) { stop1 = true; }

		bvec vec(it1, it2);
		if (vec.size() > 0) {
			//cout << "SPLIT VECTOR: ";
			//for (bvec_size i = 0; i < vec.size(); ++i) {
			//	cout << vec[i];
			//}
			//cout << "\n";
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
	//cout << "CALCULATED NUMBER OF POINTS EXCLUDING ZERO AND INFINITY: " << num_pts << "\n";
	pts = num_pts;
	stop1 = false, stop2 = false;
	counter = 1;
	//VB is the vector containing the split second number B as separate bin_ints.
	it1 = B.N.begin(), it2 = B.N.begin() + aux5;
	while (!stop1) {
		if (stop2) { stop1 = true; }
		bvec vec(it1, it2);
		if (vec.size() > 0) {
		//	cout << "SPLIT VECTOR: ";
			//for (bvec_size i = 0; i < vec.size(); ++i) {
			//	cout << vec[i];
			//}
		//	cout << "\n";

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
	//cout << "The split number A is:\n";
	//for (bvec_size i = 0; i < VA.size(); ++i) {
	//	cout << VA[i] << " ";
	//}
	//cout << "\nThe split number B is:\n";
	//for (bvec_size i = 0; i < VB.size(); ++i) {
	//	cout << VB[i] << " ";
	//}
	//cout << "\n";
	counter = 1;
	if (num_pts > 0) {
		//cout << "Please input " << num_pts << " points in binary. LSB is the leftmost bit.\n";
		//The vector of binary integers containing the points to evaluate at.
		string p1 = "1000000000000000", p2 = "1111111111111111111111", p3 = "0111111111111111111111";
		//while (counter <= (num_pts)) {
		//	cin >> s;
		//	V.push_back(bin_int(s));
		//	++counter;
		//}
		V.push_back(bin_int(p1));
		V.push_back(bin_int(p2));
		V.push_back(bin_int(p3));
		//cout << "The vector of evaluation points excluding zero and infinity:\n";
		//for (bvec_size i = 0; i < V.size(); ++i) {
		//	cout << V[i] << " ";
		//}
		//cout << "\n";
	}
	//=============================================================================================
	VC.push_back(*(VA.end() - 1)), VD.push_back(*(VB.end() - 1));
	VC.push_back(*(VA.begin())), VD.push_back(*(VB.begin()));
	--pts;
	while (pts >= 0) {
		counter = aux - 2;
		point = V[pts];
		Gpoint = point;
		//cout << "POINT: " << point << "\n";
		for (vector<bin_int>::size_type i = 0; i < VA.size(); ++i) {
			//cout << "\t=========================================================================\n";
		//	cout << "\tTerms: VA[" << i << "] = " << VA[i] << ", VB[" << i << "] = " << VB[i] << "\n";
			if (!(i == VA.size() - 1)) {
				while (counter > i) {
			//		cout << "POINT TIMES POINT: ";
					Gpoint *= point;
			//		cout << Gpoint << "\n";
					--counter;
				}
				counter = aux - 2;
			//	cout << "\tPoint to multiply terms by: " << Gpoint << "\n";

				G1 = VA[i] * Gpoint;
				G2 = VB[i] * Gpoint;
			}
			else {
				G1 = VA[i];
				G2 = VB[i];
			}
		//	cout << "\tResult: G1 = " << G1 << ", G2 = " << G2 << "\n";
			Gpoint = point;

			acc1 += G1;
			acc2 += G2;
			G1 = zero, G2 = zero;
		}
	//	cout << "\tEVALUATION: \n";
	//	cout << "\t\tC(p) = " << acc1;
	//	cout << "\n\t\tD(p) = " << acc2 << "\n";
		//cout << "\t=========================================================================\n";
		VC.push_back(acc1), VD.push_back(acc2);
		acc1 = zero, acc2 = zero;
		--pts;
	}
	//cout << "The two evaluation vectors are:\n";
	//cout << "The evaluation vector VC of As:\n";
	//for (bvec_size i = 0; i < VC.size(); ++i) {
	//	cout << VC[i] << " ";
	//}
	//cout << "\nThe evaluation vector VD of Bs:\n";
	//for (bvec_size i = 0; i < VD.size(); ++i) {
	//	cout << VD[i] << " ";
	//}
	//cout << "\n";
	//==============================================================================================
	//Multiply each entry C(p) by each entry D(p) to get evaluation values E(p).
	for (vector<bin_int>::size_type i = 0; i < VD.size(); ++i) {
		VE.push_back(VC[i] * VD[i]);
	}
	//cout << "\nThe final evaluation vector VE:\n";
	//for (bvec_size i = 0; i < VE.size(); ++i) {
	//	cout << VE[i] << " ";
	//}
	//cout << "\n";
	//==============================================================================================
	aux1 = (2 * aux) - 2;
	VX.push_back(One1);
	while (aux1 > 0) {
		VX.push_back(zero);
		--aux1;
	}
	VX.push_back(VE[1]);
	VZ.push_back(VX);
	VX = {};
	counter = num_pts;
	while (counter > 0) {
		point = V[counter - 1];
	//	cout << "POINT: " << point << "\n";
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
		//	cout << "\tPoint to push pack: " << Gpoint << "\n";
			VX.push_back(Gpoint);
			Gpoint = point;
			--aux1;
		}
		VX.push_back(One1);
		//cout << "\tLastly, pushing back VE[" << VE.size() - counter << "] = " << VE[VE.size() - counter] << "\n";
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
	VX.push_back(VE[0]);
	VZ.push_back(VX);

	/*cout << "The matrix of equations to be solved:\n";
	for (vector<bin_int>::size_type i = 0; i < VZ.size(); ++i) {
		for (vector<bin_int>::size_type j = 0; j < VZ[i].size(); ++j) {
			cout << VZ[i][j] << " ";
		}
		cout << "\n";
	}*/
	//========================================================================================
	Solve(VZ);
	//========================================================================================
	bvec_size doublesize = (old_size * 2) + 1;
	vector<bvec> VR;

	VR.push_back((((VZ.end() - 1)->end() - 1)->N));

	for (vector<vector<bin_int>>::iterator i = VZ.end() - 2; i > VZ.begin(); --i) {
		VR.push_back(((*i).end() - 1)->N);
	}

	VR.push_back(((VZ[0].end() - 1)->N));

	for (vector<bvec>::iterator i = VR.begin(); i != VR.end(); ++i) {
		while (i->size() < doublesize) {
			i->push_back(false);
		}
	}

	short j = aux5;
	for (vector<bvec>::iterator i = VR.begin() + 1; i != VR.end(); ++i) {
		for (short k = j; k > 0; --k) {
			i->erase(i->end() - 1);
			i->insert(i->begin(), 1, false);
		}
		j += aux5;
	}
	vector<bin_int> VRes;
	for (vector<bvec>::iterator i = VR.begin(); i < VR.end(); ++i) {
		VRes.push_back(bin_int(*i));
	}
	for (vector<bin_int>::iterator i = VRes.begin() + 1; i < VRes.end(); ++i) {
	//	cout << "\nAdding: " << VRes[0] << " + " << *i;
		VRes.begin()->operator+=(*i);
	}
	//cout << VRes[0] << "\n";
	BITSIZE = old_size;
	return VRes.begin()->N;
}
#endif
