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

class Sudoku : public Space {
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
    Sudoku(void) : l(*this, BOARD_SIZE * BOARD_SIZE, 1, 9) {

        printLabel();
        
        //rows
        for (int i = 0; i < BOARD_SIZE; i++) {
            distinct(*this, l.slice(i * BOARD_SIZE, 1, BOARD_SIZE));
        }
         
        //columns
        for (int i = 0; i < BOARD_SIZE; i++) {
            distinct(*this, l.slice(i, BOARD_SIZE, BOARD_SIZE));
        }
        
        //squares
        for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i += BOARD_SIZE * BOARD_SIZE / 3) {
            for (int j = 0; j < BOARD_SIZE; j+= sqrt(BOARD_SIZE)) {
                IntVarArgs square;
                for (int rowNum = 0; rowNum < sqrt(BOARD_SIZE); rowNum++) {
                    square << l.slice(rowNum * BOARD_SIZE + i + j, 1, sqrt(BOARD_SIZE));
                }
                distinct(*this, square);
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
    
    Sudoku(bool share, Sudoku& s) : Space(share, s) {
        l.update(*this, share, s.l);
    }
    
    virtual Space* copy(bool share) {
        return new Sudoku(share, *this);
    }

    void print(void) const {
        for(int i = 0; i < BOARD_SIZE * BOARD_SIZE; i+= BOARD_SIZE){
            if(i % 27 == 0){
                cout << "-------------------------" <<endl;
            }
            
            cout << "|" << l[i + 0] << ", " << l[i + 1] << ", " << l[i + 2] << "|" << l[i + 3] << ", " << l[i + 4] << ", " << l[i + 5] << "|" << l[i + 6]<< ", "  << l[i + 7] << ", " << l[i + 8] << "|" <<endl;
        }
        
        cout << "-------------------------" <<endl;
        
        
        cout <<endl <<endl;
    }
};

int main(int argc, char* argv[]) {
    Sudoku* m = new Sudoku;
    Gecode::DFS<Sudoku> e(m);
    delete m;
    
    while (Sudoku* s = e.next()) {
        s->print();
        delete s;
    }
    
    return 0;
}
