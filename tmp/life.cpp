//
//  life.cpp
//  tmp
//
//  Created by Victor Axelsson on 2017-05-26.
//  Copyright © 2017 simple_solutions. All rights reserved.
//

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

class Life : public IntMaximizeScript {
        
    private:
        
    protected:
    
    IntVar aliveNodes;
    IntVarArray board;
    int n;
    
    public:

        Life(const SizeOptions& opt): IntMaximizeScript(opt), n(opt.size()),
            aliveNodes(*this, 0, opt.size() * opt.size()),
            board(*this, (opt.size() + (DEAD_ROWS * 2)) * (opt.size() + (DEAD_ROWS * 2)), 0, 1){

			//Outer rows and columns should stay dead
			int last = opt.size() + (DEAD_ROWS * 2) - 2;
			int secondToLast = opt.size() + (DEAD_ROWS * 2) - 1;

			Matrix<IntVarArray> boardAsMatrix(board, (opt.size() + (DEAD_ROWS * 2)), (opt.size() + (DEAD_ROWS * 2)));
			count(*this, boardAsMatrix.row(0), 1, IRT_EQ, 0);
			count(*this, boardAsMatrix.row(1), 1, IRT_EQ, 0);
			count(*this, boardAsMatrix.row(secondToLast), 1, IRT_EQ, 0);
			count(*this, boardAsMatrix.row(last), 1, IRT_EQ, 0);

			count(*this, boardAsMatrix.col(0), 1, IRT_EQ, 0);
			count(*this, boardAsMatrix.col(1), 1, IRT_EQ, 0);
			count(*this, boardAsMatrix.col(secondToLast), 1, IRT_EQ, 0);
			count(*this, boardAsMatrix.col(last), 1, IRT_EQ, 0);
            


            std::cout << "In ctor. N:" << n;
            
        }
    
        Life(bool share, Life& tmp) : IntMaximizeScript(share, tmp) {
            aliveNodes = tmp.aliveNodes;
            n = tmp.n;
        }
        
        virtual Space* copy(bool share) {
            return new Life(share, *this);
        }
    
        // cost function
        virtual IntVar cost(void) const {
            return aliveNodes;
        }
    
    
        //Print solution
        virtual void print(std::ostream& os) const {
            
                   // os << "  -fill "<< colors[i % 7] <<" -draw \" rectangle " << x1 << "," << y1 <<" " << x2 <<"," << y2  << "\" ";
        }
    };
    
    int main(int argc, char* argv[]) {
        
        SizeOptions opt("Life");
        opt.size(6);

        IntMaximizeScript::run<Life, BAB, SizeOptions>(opt);
        
        return 0;
    }
