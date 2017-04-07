//
//  Sudoku.cpp
//  tmp
//
//  Created by Victor Axelsson on 2017-04-03.
//  Copyright © 2017 simple_solutions. All rights reserved.
//

#include <stdio.h>
#include <gecode/int.hh>
#include <gecode/search.hh>
#include <gecode/driver.hh>

using namespace Gecode;
using namespace std;

const int CHESSBOARD_SIZE = 9;

class QueensN : public Script {
protected:
	IntVarArray l;

public:
	QueensN(const SizeOptions& opt)
		: Script(opt), l(*this, CHESSBOARD_SIZE * CHESSBOARD_SIZE, 0, 1) {

		Matrix<IntVarArgs> mat(l, CHESSBOARD_SIZE, CHESSBOARD_SIZE);
		IntArgs c(CHESSBOARD_SIZE);
		for (int i = 0; i < CHESSBOARD_SIZE; i++) {
			c[i] = 1;
		}
		//rows
		for (int i = 0; i < CHESSBOARD_SIZE; i++) {
			linear(*this, c, l.slice(i * CHESSBOARD_SIZE, 1, CHESSBOARD_SIZE), IRT_EQ, 1);
		}

		//columns
		for (int i = 0; i < CHESSBOARD_SIZE; i++) {
			linear(*this, c, l.slice(i, CHESSBOARD_SIZE, CHESSBOARD_SIZE), IRT_EQ, 1);
		}

		//diagonals
		for (int i = 0; i < CHESSBOARD_SIZE; i++) {
			int row = i;
			int col = 0;
			IntVarArgs diag;
			while (row < CHESSBOARD_SIZE && col < CHESSBOARD_SIZE) {
				diag << l[row * CHESSBOARD_SIZE + col];
				row++;
				col++;
			}
			if (diag.size() > 1) {
				IntArgs k(diag.size());
				for (int s = 0; s < diag.size(); s++) {
					k[s] = 1;
				}
				linear(*this, k, diag, IRT_LQ, 1);
			}
		}

		for (int i = 1; i < CHESSBOARD_SIZE; i++) {
			int col = i;
			int row = 0;
			IntVarArgs diag;
			while (row < CHESSBOARD_SIZE && col < CHESSBOARD_SIZE) {
				diag << l[row * CHESSBOARD_SIZE + col];
				row++;
				col++;
			}
			if (diag.size() > 1) {
				IntArgs k(diag.size());
				for (int s = 0; s < diag.size(); s++) {
					k[s] = 1;
				}
				linear(*this, k, diag, IRT_LQ, 1);
			}
		}
		
		for (int i = 0; i < CHESSBOARD_SIZE; i++) {
			int col = CHESSBOARD_SIZE - 1;
			int row = i;
			IntVarArgs diag;
			while (row < CHESSBOARD_SIZE && col >= 0) {
				diag << l[row * CHESSBOARD_SIZE + col];
				row++;
				col--;
			}
			if (diag.size() > 1) {
				IntArgs k(diag.size());
				for (int s = 0; s < diag.size(); s++) {
					k[s] = 1;
				}
				linear(*this, k, diag, IRT_LQ, 1);
			}
		}
		for (int i = CHESSBOARD_SIZE - 2; i >= 0; i--) {
			int row = 0;
			int col = i;
			IntVarArgs diag;
			while (row < CHESSBOARD_SIZE && col >= 0) {
				diag << l[row * CHESSBOARD_SIZE + col];
				row++;
				col--;
			}
			if (diag.size() > 1) {
				IntArgs k(diag.size());
				for (int s = 0; s < diag.size(); s++) {
					k[s] = 1;
				}
				linear(*this, k, diag, IRT_LQ, 1);
			}
		}

		//branch(*this, l, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
		branch(*this, l, INT_VAR_MERIT_MIN(&m), INT_VAL_MIN());

		//branch(*this, l, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
	}

	static double m(const Space& home, IntVar x, int i) {
		return abs((CHESSBOARD_SIZE / 2) - (i % CHESSBOARD_SIZE));
	}

	QueensN(bool share, QueensN& s) : Script(share, s) {
		l.update(*this, share, s.l);
	}

	virtual Space* copy(bool share) {
		return new QueensN(share, *this);
	}

	void print(void) const {
		cout << endl;
		for (int i = 0; i < CHESSBOARD_SIZE; i += 1) {
			cout << endl;
			for (int j = 0; j < CHESSBOARD_SIZE; j += 1) {
				cout << l[i * CHESSBOARD_SIZE + j] << " ";
			}
		}
	}

	/// Print solution
	virtual void
		print(std::ostream& os) const {
		os << "queens\t";
		for (int i = 0; i < l.size(); i++) {
			os << l[i] << ", ";
			if ((i + 1) % 10 == 0)
				os << std::endl << "\t";
		}
		os << std::endl;
	}
};

