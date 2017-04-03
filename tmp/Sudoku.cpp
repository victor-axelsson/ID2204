//
//  Sudoku.cpp
//  tmp
//
//  Created by Victor Axelsson on 2017-04-03.
//  Copyright © 2017 simple_solutions. All rights reserved.
//

#include <stdio.h>


#include <stdio.h>
#include <gecode/int.hh>
#include <gecode/search.hh>
#include "A1.cpp"

using namespace Gecode;
using namespace std;

const int BOARD_INSTANCE = 1;
const int BOARD_SIZE = 9;

class Sudoku : public Space {
protected:
    IntVarArray l;

 
public:
    Sudoku(void) : l(*this, BOARD_SIZE * BOARD_SIZE, 1, 9) {

        cout << "In CTOR" <<endl;
        
        
         //rows
         for (int i = 0; i < BOARD_SIZE; i++) {
            distinct(*this, l.slice(i * BOARD_SIZE, 1, BOARD_SIZE));
         }
         
         //columns
         for (int i = 0; i < BOARD_SIZE; i++) {
             distinct(*this, l.slice(i, BOARD_SIZE, BOARD_SIZE));
         }
        
        //squares
        IntVarArgs square1;
        square1 << l.slice(0, 1, sqrt(BOARD_SIZE));
        square1 << l.slice(9, 1, sqrt(BOARD_SIZE));
        square1 << l.slice(18, 1, sqrt(BOARD_SIZE));
        distinct(*this, square1);
        
        IntVarArgs square2;
        square2 << l.slice(3, 1, sqrt(BOARD_SIZE));
        square2 << l.slice(12, 1, sqrt(BOARD_SIZE));
        square2 << l.slice(21, 1, sqrt(BOARD_SIZE));
        distinct(*this, square2);
        
        IntVarArgs square3;
        square3 << l.slice(6, 1, sqrt(BOARD_SIZE));
        square3 << l.slice(15, 1, sqrt(BOARD_SIZE));
        square3 << l.slice(24, 1, sqrt(BOARD_SIZE));
        distinct(*this, square3);
        
        
        IntVarArgs square4;
        square4 << l.slice(27, 1, sqrt(BOARD_SIZE));
        square4 << l.slice(36, 1, sqrt(BOARD_SIZE));
        square4 << l.slice(45, 1, sqrt(BOARD_SIZE));
        distinct(*this, square4);
        
        IntVarArgs square5;
        square5 << l.slice(30, 1, sqrt(BOARD_SIZE));
        square5 << l.slice(39, 1, sqrt(BOARD_SIZE));
        square5 << l.slice(48, 1, sqrt(BOARD_SIZE));
        distinct(*this, square5);
        
        IntVarArgs square6;
        square6 << l.slice(33, 1, sqrt(BOARD_SIZE));
        square6 << l.slice(42, 1, sqrt(BOARD_SIZE));
        square6 << l.slice(51, 1, sqrt(BOARD_SIZE));
        distinct(*this, square6);
        
        
        IntVarArgs square7;
        square7 << l.slice(54, 1, sqrt(BOARD_SIZE));
        square7 << l.slice(63, 1, sqrt(BOARD_SIZE));
        square7 << l.slice(72, 1, sqrt(BOARD_SIZE));
        distinct(*this, square7);
        
        IntVarArgs square8;
        square8 << l.slice(57, 1, sqrt(BOARD_SIZE));
        square8 << l.slice(66, 1, sqrt(BOARD_SIZE));
        square8 << l.slice(75, 1, sqrt(BOARD_SIZE));
        distinct(*this, square8);
        
        IntVarArgs square9;
        square9 << l.slice(60, 1, sqrt(BOARD_SIZE));
        square9 << l.slice(69, 1, sqrt(BOARD_SIZE));
        square9 << l.slice(78, 1, sqrt(BOARD_SIZE));
        distinct(*this, square9);
        
        /*
        //squares
        for (int i = 0; i < BOARD_SIZE; i++) {
            distinct(*this, l.slice(i * 3, sqrt(BOARD_SIZE), BOARD_SIZE));
        }
        */
        
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
    
    Sudoku(bool share, Sudoku& s) : Space(share, s) {
        l.update(*this, share, s.l);
    }
    
    virtual Space* copy(bool share) {
        return new Sudoku(share, *this);
    }

    /*
    void print(std::ostream& os) const {
        os << l << std::endl;
    }
    */
    
    void print(void) const {
        
        cout << "-------------------------" <<endl;
        for(int i = 0; i < BOARD_SIZE * BOARD_SIZE; i+= BOARD_SIZE){
            cout << "|" << l[i + 0] << ", " << l[i + 1] << ", " << l[i + 2] << "|" << l[i + 3] << ", " << l[i + 4] << ", " << l[i + 5] << "|" << l[i + 6]<< ", "  << l[i + 7] << ", " << l[i + 8] << "|" <<endl;
            cout << "-------------------------" <<endl;
            
        }
        
        cout <<endl <<endl;
    }
};
