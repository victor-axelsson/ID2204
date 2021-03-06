//
//  life.cpp
//  tmp
//
//  Created by Victor Axelsson on 2017-05-26.
//  Copyright © 2017 simple_solutions. All rights reserved.
//

/*

====================== Solutions for 8 without optimizations ======================

0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0
0  0  1  1  1  1  1  1  1  1  0  0
0  0  1  0  0  1  0  0  0  1  0  0
0  0  1  0  0  0  0  1  1  0  0  0
0  0  1  1  1  1  1  1  0  0  0  0
0  0  0  0  0  0  0  0  0  1  0  0
0  0  1  1  0  1  1  0  1  1  0  0
0  0  1  1  0  1  0  0  0  1  0  0
0  0  0  0  0  0  1  1  1  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0
COUNT: 34


0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0
0  0  1  1  1  1  1  1  1  1  0  0
0  0  1  0  0  1  0  0  0  1  0  0
0  0  1  0  0  0  0  1  1  0  0  0
0  0  1  1  1  1  1  0  0  0  0  0
0  0  0  0  0  0  0  1  1  0  0  0
0  0  1  1  1  1  0  1  0  1  0  0
0  0  1  0  0  1  0  1  0  1  0  0
0  0  0  1  1  0  0  0  1  1  0  0
0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0
COUNT: 35

0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0
0  0  1  1  1  1  1  1  1  1  0  0
0  0  1  0  0  1  0  0  0  1  0  0
0  0  1  0  0  0  0  1  0  1  0  0
0  0  1  1  1  1  1  1  1  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0
0  0  1  1  1  1  1  1  1  0  0  0
0  0  1  0  0  0  0  0  0  1  0  0
0  0  0  1  1  1  1  1  1  1  0  0
0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0
COUNT: 37

0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0
0  0  1  1  1  1  1  1  1  1  0  0
0  0  1  0  0  0  0  0  0  1  0  0
0  0  1  0  1  1  1  1  1  0  0  0
0  0  1  0  1  0  0  0  0  0  0  0
0  0  1  0  1  0  1  1  1  0  0  0
0  0  1  0  1  1  0  1  0  1  0  0
0  0  1  0  0  0  0  0  0  1  0  0
0  0  1  1  1  1  1  1  1  1  0  0
0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0
COUNT: 38

0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0
0  0  1  1  1  1  1  1  1  1  0  0
0  0  1  0  0  0  0  0  0  1  0  0
0  0  1  0  1  1  1  1  0  1  0  0
0  0  1  0  1  0  0  1  0  1  0  0
0  0  1  0  1  0  0  1  0  1  0  0
0  0  1  0  1  1  1  1  0  1  0  0
0  0  1  0  0  0  0  0  0  1  0  0
0  0  1  1  1  1  1  1  1  1  0  0
0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0
COUNT: 40

====================== Solutions for 9 ======================

0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  1  1  1  1  1  1  1  1  1  0  0
0  0  1  0  0  1  0  0  0  0  1  0  0
0  0  1  0  0  0  0  1  1  1  0  0  0
0  0  1  1  1  1  1  1  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  1  1  1  1  1  1  1  1  0  0  0
0  0  1  0  0  1  0  0  1  0  1  0  0
0  0  1  0  0  0  0  0  0  0  1  0  0
0  0  1  1  1  1  1  1  1  1  1  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0
COUNT: 45

0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  1  1  1  1  1  1  1  1  1  0  0
0  0  1  0  0  1  0  0  0  0  1  0  0
0  0  1  0  0  0  0  1  1  1  0  0  0
0  0  1  1  1  1  1  0  1  0  0  0  0
0  0  0  0  0  1  0  0  0  0  1  0  0
0  0  1  1  0  0  0  1  1  1  1  0  0
0  0  1  0  1  1  1  1  0  0  0  0  0
0  0  1  0  0  0  0  0  0  1  1  0  0
0  0  1  1  1  1  1  1  1  0  1  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0
COUNT: 46

0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  1  1  1  1  1  1  1  1  1  0  0
0  0  1  0  0  1  0  0  0  0  1  0  0
0  0  1  0  0  0  0  1  1  0  1  0  0
0  0  1  1  1  1  1  1  0  1  1  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  1  1  1  1  1  1  1  1  1  0  0
0  0  1  0  0  1  0  0  0  0  1  0  0
0  0  1  0  0  0  0  1  1  0  1  0  0
0  0  1  1  1  1  1  1  0  1  1  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0
COUNT: 48


*/

#include <stdio.h>
#include <gecode/int.hh>
#include <gecode/search.hh>
#include <gecode/driver.hh>
#include <math.h>
#include <gecode/minimodel.hh>
#include <string>


using namespace Gecode;
using namespace std;
const int NR_OF_ITEMS = 6;
const int DEAD_ROWS = 2;

class Life : public Script {
        
    private:
    
    void printKitten() const {
        
        string s = "\n";
        s += "                                            .--. \n";
        s += "                                             `.  \\ \n";
        s += "                                               \\  \\ \n";
        s += "                                                .  \\ \n";
        s += "                                                :   . \n";
        s += "                                                |    . \n";
        s += "                                                |    : \n";
        s += "                                                |    | \n";
        s += "  ..._  ___                                     |    | \n";
        s += " `.\"\".`''''\"\"--..___                            |    | \n";
        s += " ,-\\  \\             ""-...__         _____________/    | \n";
        s += " / ` \" '                  `\"\"\"\"\"\"\"\"                   . \n";
        s += " \\                                                     L \n";
        s += " (>                                                      \\ \n";
        s += "/                                                         \\ \n";
        s += "\\_    ___..---.                                            L \n";
        s += "  `--'         '.                                           \\ \n";
        s += "                 .                                           \\_ \n";
        s += "                _/`.                                           `.._ \n";
        s += "             .'     -.                                             `. \n";
        s += "            /     __.-Y     /''''''-...___,...--------.._            | \n";
        s += "           /   _.\"    |    /                ' .      \\   '---..._    | \n";
        s += "          /   /      /    /                _,. '    ,/           |   | \n";
        s += "          \\_,'     _.'   /              /''     _,-'            _|   | \n";
        s += "                  '     /               `-----''               /     | \n";
        s += "                  `...-'     GAME OF LIFE                      `...-' \n";
        s += " \n";
        cout << s;
    }
        
    protected:
    
    IntVarArray board;
    int n;

	//Optimization
	IntVarArray squareSums;
    
    public:

        Life(const SizeOptions& opt): Script(opt), n(opt.size()),
            board(*this, (opt.size() + (DEAD_ROWS * 2)) * (opt.size() + (DEAD_ROWS * 2)), 0, 1),
			squareSums(*this, ((opt.size() / 3) * (opt.size() / 3)), 0, 6) {

			//Outer rows and columns should stay dead
			int last = n + (DEAD_ROWS * 2) - 2;
			int secondToLast = n + (DEAD_ROWS * 2) - 1;

			Matrix<IntVarArray> boardAsMatrix(board, (n + (DEAD_ROWS * 2)), (n + (DEAD_ROWS * 2)));
			count(*this, boardAsMatrix.row(0), 1, IRT_EQ, 0);
			count(*this, boardAsMatrix.row(1), 1, IRT_EQ, 0);
			count(*this, boardAsMatrix.row(secondToLast), 1, IRT_EQ, 0);
			count(*this, boardAsMatrix.row(last), 1, IRT_EQ, 0);

			count(*this, boardAsMatrix.col(0), 1, IRT_EQ, 0);
			count(*this, boardAsMatrix.col(1), 1, IRT_EQ, 0);
			count(*this, boardAsMatrix.col(secondToLast), 1, IRT_EQ, 0);
			count(*this, boardAsMatrix.col(last), 1, IRT_EQ, 0);
            
			int tmpInd = 0;

			for (int i = DEAD_ROWS; i < n + DEAD_ROWS; i++) {
				for (int j = DEAD_ROWS; j < n + DEAD_ROWS; j++) {
					//By rules of the game we need still life, so dead cells should be constrained to stay dead,
					//while living cells should not die. Here we take all of the neighbours of the cell and do the proper checks using sums
					IntVarArray neighbourCells(*this, 8, 0, 1);
					neighbourCells[0] = boardAsMatrix(i - 1, j - 1);   
					neighbourCells[1] = boardAsMatrix(i + 1, j - 1);   
					neighbourCells[2] = boardAsMatrix(i, j - 1);      
					neighbourCells[3] = boardAsMatrix(i - 1, j + 1);  
					neighbourCells[4] = boardAsMatrix(i, j + 1);       
					neighbourCells[5] = boardAsMatrix(i + 1, j + 1);   
					neighbourCells[6] = boardAsMatrix(i - 1, j);    
					neighbourCells[7] = boardAsMatrix(i + 1, j);

					rel(*this, (boardAsMatrix(i, j) == 1 && (sum(neighbourCells) == 2 || sum(neighbourCells) == 3)) || // if the cell is alive, it should stay alive, so 2 or 3 neighbours alive
						(boardAsMatrix(i, j) == 0 && sum(neighbourCells) != 3));									     // if the cell is dead, it should not have 3 neighbours

					//Each 3x3 square can have max 6 live cells. tmpInd keeps track of which square we are in now
					if (i % 3 == 2 && j % 3 == 2 && i < n && j < n) {
						rel(*this, squareSums[tmpInd] == sum(boardAsMatrix.slice(i, i + 3, j, j + 3)));
						tmpInd += 1;
					}
				}
			}

            LinIntExpr(sum(board)).post(*this, IPL_VAL);
                
			branch(*this, board, INT_VAR_NONE(), INT_VAL_MAX());
        }
    
        Life(bool share, Life& tmp) : Script(share, tmp) {
            n = tmp.n;
			board.update(*this, share, tmp.board);
			squareSums.update(*this, share, tmp.squareSums);
        }
    
       virtual void constrain(const Space& b) {
           const Life& life = static_cast<const Life&>(b);
           rel(*this, sum(board) > sum(life.board));
        }
    
        virtual Space* copy(bool share) {
            return new Life(share, *this);
        }
    
        //Print solution
        virtual void print(std::ostream& os) const {
            
        
            printKitten();
            
            int sum = 0;
            for(int i = 0; i < (n + 4) * (n + 4); i++){
                if(i % (n + 4) == 0){
                    os << endl;
                }
            
                if(board[i].assigned()){
                    os << " "  << board[i].min() << " ";
                    sum += board[i].val();
                }else{
                    os << " ? ";
                }
            }
            
            os <<endl << " COUNT: " << sum <<endl;
        }
    };
    
    int main(int argc, char* argv[]) {
        
        SizeOptions opt("Life");
		opt.solutions(0);
        opt.size(8);

        IntMaximizeScript::run<Life, BAB, SizeOptions>(opt);
        
        return 0;
    }
