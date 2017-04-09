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
#include "A1.cpp"

using namespace Gecode;
using namespace std;

//What instance from the examples we are gonna use
const int BOARD_INSTANCE = 2;

//Size of the board, (length of the side)
const int BOARD_SIZE = 9;

class Sudoku : public Script {
protected:
    IntVarArray l;
 
    void printLabel(){
       cout << "         ______________________________________        " <<endl;
       cout << " ________|                                     |_______" <<endl;
       cout << " \\       |            SUDOKU MAZTERZ           |      /" <<endl;
       cout << "  \\      |                                     |     /  " <<endl;
       cout << "  /      |_____________________________________|     \\  " <<endl;
       cout << " /__________)                               (_________\\" <<endl <<endl;

    }
    
public:
	enum {
		ICL_DEF, ICL_VAL, ICL_BND, ICL_DOM
	}; 
	void addDistinct(IntVarArgs array, SizeOptions opt, Sudoku& s) {
		switch (opt.branching()) {
		case ICL_DEF:
			cout << "ICL_DEF" << endl;
			distinct(s, array, IPL_DEF);
			break;

		case ICL_VAL:
			cout << "ICL_VAL" << endl;
			distinct(s, array, IPL_VAL);
			break;

		case ICL_BND:
			cout << "ICL_VAL" << endl;
			distinct(s, array, IPL_BND);
			break;

		case ICL_DOM:
			cout << "ICL_DOM" << endl;
			distinct(s, array, IPL_DOM);
			break;

		default:
			cout << "Default" << endl;
			//Default
			distinct(s, array);
			break;
		}
	};

	Sudoku(const SizeOptions& opt)
		: Script(opt), l(*this, BOARD_SIZE * BOARD_SIZE, 1, 9) {

        printLabel();
        
        //rows
        for (int i = 0; i < BOARD_SIZE; i++) {
			//addDistinct(l.slice(i * BOARD_SIZE, 1, BOARD_SIZE), opt, *this);
			switch (opt.branching()) {
			case ICL_DEF:
				cout << "ICL_DEF" << endl;
				distinct(*this, l.slice(i * BOARD_SIZE, 1, BOARD_SIZE), IPL_DEF);
				break;

			case ICL_VAL:
				cout << "ICL_VAL" << endl;
				distinct(*this, l.slice(i * BOARD_SIZE, 1, BOARD_SIZE), IPL_VAL);
				break;

			case ICL_BND:
				cout << "ICL_VAL" << endl;
				distinct(*this, l.slice(i * BOARD_SIZE, 1, BOARD_SIZE), IPL_BND);
				break;

			case ICL_DOM:
				cout << "ICL_DOM" << endl;
				distinct(*this, l.slice(i * BOARD_SIZE, 1, BOARD_SIZE), IPL_DOM);
				break;

			default:
				cout << "Default" << endl;
				//Default
				distinct(*this, l.slice(i * BOARD_SIZE, 1, BOARD_SIZE));
				break;
			}
        }
         
        //columns
        for (int i = 0; i < BOARD_SIZE; i++) {
			//addDistinct(l.slice(i, BOARD_SIZE, BOARD_SIZE), opt, *this);
			switch (opt.branching()) {
			case ICL_DEF:
				cout << "ICL_DEF" << endl;
				distinct(*this, l.slice(i, BOARD_SIZE, BOARD_SIZE), IPL_DEF);
				break;

			case ICL_VAL:
				cout << "ICL_VAL" << endl;
				distinct(*this, l.slice(i, BOARD_SIZE, BOARD_SIZE), IPL_VAL);
				break;

			case ICL_BND:
				cout << "ICL_VAL" << endl;
				distinct(*this, l.slice(i, BOARD_SIZE, BOARD_SIZE), IPL_BND);
				break;

			case ICL_DOM:
				cout << "ICL_DOM" << endl;
				distinct(*this, l.slice(i, BOARD_SIZE, BOARD_SIZE), IPL_DOM);
				break;

			default:
				cout << "Default" << endl;
				//Default
				distinct(*this, l.slice(i, BOARD_SIZE, BOARD_SIZE));
				break;
			}
        }
        
        //squares
        for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i += BOARD_SIZE * BOARD_SIZE / 3) {
            for (int j = 0; j < BOARD_SIZE; j+= sqrt(BOARD_SIZE)) {
                IntVarArgs square;
                for (int rowNum = 0; rowNum < sqrt(BOARD_SIZE); rowNum++) {
                    square << l.slice(rowNum * BOARD_SIZE + i + j, 1, sqrt(BOARD_SIZE));
                }
				//addDistinct(square, opt);
				switch (opt.branching()) {
				case ICL_DEF:
					distinct(*this, square, IPL_DEF);
					break;

				case ICL_VAL:
					distinct(*this, square, IPL_VAL);
					break;

				case ICL_BND:
					cout << "ICL_VAL" << endl;
					distinct(*this, square, IPL_BND);
					break;

				case ICL_DOM:
					cout << "ICL_DOM" << endl;
					distinct(*this, square, IPL_DOM);
					break;

				default:
					cout << "Default" << endl;
					//Default
					distinct(*this, square);
					break;
				}
            }
        }
   
        
        //Add the constraints from the board
        for(int i = 0; i < BOARD_SIZE; i++){
            for (int j = 0; j < BOARD_SIZE; j++){
                
                int curr = examples[BOARD_INSTANCE][i][j];
                
                if(curr != 0){
                    
                    //Add equals constaint
                    rel(*this, l[i * BOARD_SIZE + j], IRT_EQ, curr);
                }
            }
        }
        
        branch(*this, l, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
    }

	
    
    Sudoku(bool share, Sudoku& s) : Script(share, s) {
        l.update(*this, share, s.l);
    }
    
    virtual Space* copy(bool share) {
        return new Sudoku(share, *this);
    }

	virtual void
		print(std::ostream& os) const {
        for(int i = 0; i < BOARD_SIZE * BOARD_SIZE; i+= BOARD_SIZE){
            if(i % 27 == 0){
				os << "-------------------------" <<endl;
            }
            
			os << "|" << l[i + 0] << ", " << l[i + 1] << ", " << l[i + 2] << "|" << l[i + 3] << ", " << l[i + 4] << ", " << l[i + 5] << "|" << l[i + 6]<< ", "  << l[i + 7] << ", " << l[i + 8] << "|" <<endl;
        }
        
		os << "-------------------------" <<endl;
        
        
		os <<endl <<endl;
    }
};

int main(int argc, char* argv[]) {
	SizeOptions opt("Sudoku");
    Sudoku* m = new Sudoku(opt);

	//cout << "ICL_DEF" << endl;
	//opt.branching(Sudoku::ICL_DEF);

	cout << "ICL_VAL" << endl;
    opt.branching(Sudoku::ICL_VAL);

	//cout << "ICL_BND" << endl;
    //opt.branching(Sudoku::ICL_BND);

	//cout << "ICL_DOM" << endl;
    //opt.branching(Sudoku::ICL_DOM);

	Script::run<Sudoku, DFS, SizeOptions>(opt);
    return 0;
}
