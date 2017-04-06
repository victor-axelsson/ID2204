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

const int CHESSBOARD_SIZE = 4;

class QueensN : public Space {
protected:
	IntVarArray l;

public:
	QueensN(void) : l(*this, CHESSBOARD_SIZE * CHESSBOARD_SIZE, 0, 1) {

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

				cout << row << ' ' << col << ' ';
				diag << l[row * CHESSBOARD_SIZE + col];
				row++;
				col++;
			}
			cout << endl;
			cout << diag << endl;
			if (diag.size() > 1) {
				IntArgs k(diag.size());
				for (int s = 0; s < diag.size(); s++) {
					k[s] = 1;
				}
				cout << k << endl;
				linear(*this, k, diag, IRT_EQ, 1);
			}
		}

		for (int i = 1; i < CHESSBOARD_SIZE; i++) {
			int col = i;
			int row = 0;
			IntVarArgs diag;
			while (row < CHESSBOARD_SIZE && col < CHESSBOARD_SIZE) {
				cout << row << ' ' << col << ' ';
				diag << l[row * CHESSBOARD_SIZE + col];
				row++;
				col++;
			}
			cout << endl;
			cout << diag << endl;
			if (diag.size() > 1) {
				IntArgs k(diag.size());
				for (int s = 0; s < diag.size(); s++) {
					k[s] = 1;
				}
				cout << k << endl;
				linear(*this, k, diag, IRT_EQ, 1);
			}
		}

		/*
		for (int i = 1; i < CHESSBOARD_SIZE; i++) {
			int col = CHESSBOARD_SIZE;
			int row = 0;
			IntVarArgs diag;
			while (row < CHESSBOARD_SIZE && col < CHESSBOARD_SIZE) {
				diag << l[row * CHESSBOARD_SIZE + col];
				row++;
				col--;
			}
			if (diag.size() > 1) {
				IntArgs k(diag.size());
				for (int s = 0; s < diag.size(); s++) {
					k[s] = 1;
				}
				linear(*this, k, diag, IRT_EQ, 1);
			}
		}
		for (int i = 0; i < CHESSBOARD_SIZE; i++) {
			int row = 0;
			int col = CHESSBOARD_SIZE - 1;
			IntVarArgs diag;
			while (row < CHESSBOARD_SIZE && col < CHESSBOARD_SIZE) {
				diag << l[row * CHESSBOARD_SIZE + col];
				row++;
				col--;
			}
			if (diag.size() > 1) {
				IntArgs k(diag.size());
				for (int s = 0; s < diag.size(); s++) {
					k[s] = 1;
				}
				linear(*this, k, diag, IRT_EQ, 1);
			}
		}
		*/


		branch(*this, l, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
	}

	QueensN(bool share, QueensN& s) : Space(share, s) {
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
};
