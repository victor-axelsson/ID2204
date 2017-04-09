//
//  Sudoku.cpp
//  tmp
//
//  Created by Victor Axelsson on 2017-04-03.
//  Copyright � 2017 simple_solutions. All rights reserved.
//

#include <stdio.h>
#include <gecode/int.hh>
#include <gecode/search.hh>
#include <gecode/driver.hh>
#include <math.h>

using namespace Gecode;
using namespace std;

const int CHESSBOARD_SIZE = 6;

class QueensN : public Script {
protected:
	IntVarArray l;
    
public:
    enum{
        MAXIMIZE_ATTACKED_SQUARES_HEURISTIC,
        KNIGHTS_MOVE_HEURISTIC,
        NO_HEURISTIC,
        RANDOM_BRANCHING
    };
    
    static int prevI;
    
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
            
        //Different branching strategies. Here you can cause different heuristics and branching techniques
            switch (opt.branching()) {
            case NO_HEURISTIC:
                cout << "No heruristics" <<endl;
                branch(*this, l, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
                break;
                
            case MAXIMIZE_ATTACKED_SQUARES_HEURISTIC:
                cout << "Maximizing attacked squares" <<endl;
                branch(*this, l, INT_VAR_MERIT_MIN(&maximizeAttackedSquares), INT_VAL_MIN());
                break;
            
            case KNIGHTS_MOVE_HEURISTIC:
                cout << "Knights move (Not implemented)" <<endl;
                branch(*this, l, INT_VAR_MERIT_MAX(&knightsMove), INT_VAL_MIN());
                break;
                
            case RANDOM_BRANCHING:
                cout << "Knights move (Not implemented)" <<endl;
                branch(*this, l, INT_VAR_RND(0), INT_VAL_MIN());
                break;
                
            default:
                cout << "Default branching" <<endl;
                //Default to no heuristic
                branch(*this, l, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
                break;
        }
	}

    
	static double maximizeAttackedSquares(const Space& home, IntVar x, int i) {
        //The ith position
        int r = floor(i / CHESSBOARD_SIZE);
        int c = i % CHESSBOARD_SIZE;

        //This section can be good for debugging purposes, but these values are constant, so we don't need to calc them
        //Calc how many square we are attacking, we want to maximize this
        //int colAttack = c + (CHESSBOARD_SIZE - c) - 1;
        //int rowAttack = r + (CHESSBOARD_SIZE - r) - 1;

        //The number of diagonals we attack on the two diagonals
        int diagonalAttack = min(r, c) + min(CHESSBOARD_SIZE - c - 1, CHESSBOARD_SIZE - r - 1);
        int otherDiagonal = min(CHESSBOARD_SIZE -1 - r, c) + min (CHESSBOARD_SIZE - 1 -c, r);
        
        //cout<< "i: " << i  << " R: " << r << " C: " << c << " sumOne:" <<  diagonalAttack  << " sumTwo: " <<otherDiagonal <<endl;
        
        return diagonalAttack + otherDiagonal;
    
    }

    static double knightsMove(const Space& home, IntVar x, int i){
        
        //Here is a suggestion to two possible heuristics that could be used.
        
        /*
          1, If n is even and n ≠ 6k + 2, then place queens at (i, 2i) and (n/2 + i, 2i - 1) for i = 1, 2, ..., n / 2.
          2, If n is even and n ≠ 6k, then place queens at (i, 1 + (2i + n/2 - 3 (mod n))) and (n + 1 - i, n - (2i + n/2 - 3 (mod n))) for i = 1, 2, ..., n / 2.
          3, If n is odd, then use one of the patterns above for (n − 1) and add a queen at (n, n).
        */
        
        // Or another alternative is to:
        
        /*
          1, If the remainder from dividing N by 6 is not 2 or 3 then the list is simply all even numbers followed by all odd numbers not greater than N.
          2, Otherwise, write separate lists of even and odd numbers (i. e. 2, 4, 6, 8 — 1, 3, 5, 7).
          3, If the remainder is 2, swap 1 and 3 in odd list and move 5 to the end (i. e. 3, 1, 7, 5).
          4, If the remainder is 3, move 2 to the end of even list and 1,3 to the end of odd list (i. e. 4, 6, 8, 2 — 5, 7, 1, 3).
          5, Append odd list to the even list and place queens in the rows given by these numbers, from left to right (i. e. a2, b4, c6, d8, e3, f1, g7, h5).
        */
        
        //copy pasted from: https://en.wikipedia.org/wiki/Eight_queens_puzzle
        
        return 0;
    }
    
    
    QueensN(bool share, QueensN& s) : Script(share, s) {
		l.update(*this, share, s.l);
	}

	virtual Space* copy(bool share) {
		return new QueensN(share, *this);
	}


	//Print solution
	virtual void
		print(std::ostream& os) const {
		for (int i = 0; i < l.size(); i++) {
			os << l[i] << ", ";
			if ((i + 1) % 10 == 0)
				os << std::endl << "\t";
		}
		os << std::endl;
	}
};


int main(int argc, char* argv[]) {
    
    SizeOptions opt("QueensN");
    
    //You can select different branchings, either from the predefined or specifing some other with a merit function
    //opt.branching(QueensN::NO_HEURISTIC);
    
    opt.branching(QueensN::MAXIMIZE_ATTACKED_SQUARES_HEURISTIC);
    //opt.branching(QueensN::RANDOM_BRANCHING);
    //opt.branching(QueensN::KNIGHTS_MOVE_HEURISTIC);
    
    
    Script::run<QueensN, DFS, SizeOptions>(opt);
    
    
    return 0;
}

