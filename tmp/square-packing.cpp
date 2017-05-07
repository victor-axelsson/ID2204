//
//  square-packing.cpp
//  tmp
//
//  Created by Victor Axelsson on 2017-05-05.
//  Copyright © 2017 simple_solutions. All rights reserved.
//


#include <stdio.h>
#include <gecode/int.hh>
#include <gecode/search.hh>
#include <gecode/driver.hh>
#include <math.h>
#include <gecode/minimodel.hh>

using namespace Gecode;
using namespace std;


class SquarePacking :  public Script {
    
private:
    static int size(int i, int n){
        return n - i;
    }
    
protected:
    IntVarArray x;
    IntVarArray y;
    IntVar s;
    
public:
    
    
    SquarePacking(const SizeOptions& opt): Script(opt),
    x(*this, opt.size(), 0, opt.size()),
    y(*this, opt.size(), 0, opt.size()),
    s(*this, opt.size() + opt.size() -1, opt.size() + opt.size() -1){
        
        int n = opt.size();

        
        
        //max(*this, x, s);
        //max(*this, y, s);
        
        //Make sure the x and y are within the boundries of s
        for(int i = 0; i < n; i++){
            int xW = size(i, n);
            
            rel(*this, x[i], IRT_LQ, n - x[i].max() + xW);
            rel(*this, y[i], IRT_LQ, n - y[i].max() + xW);
        }
        
        
        
        
        
        //No overlap
        for(int i = 0; i < n; i++){
            int iSize = size(i, n);
            for(int z = i +1; z < n; z++){
                int zSize = size(z, n);
                
                
                //If x[i] is:
                BoolVar left(*this, 0, 1);
                BoolVar right(*this, 0, 1);
                BoolVar above(*this, 0, 1);
                BoolVar below(*this, 0, 1);
                
                
                rel(*this, x[z], IRT_GR, x[i].max() + iSize, left);
                rel(*this, x[i], IRT_GR, x[z].max() + zSize, right);
                rel(*this, y[i], IRT_GR, y[z].max() + zSize, below);
                rel(*this, y[z], IRT_GR, y[i].max() + iSize, above);
                
                
                /*
                int refied = 0;
                // s1 is left of s2
                refied += x[i].max() + iSize < x[z].min() ? 1 : 0;
                
                // s2 is left of s1
                refied += x[z].max() + zSize < x[i].min() ? 1 : 0;
                
                // s1 is above s2
                refied += y[i].max() + iSize < y[z].min() ? 1 : 0;
                
                // s2 is above s1
                refied += y[z].max() + zSize < y[i].min() ? 1 : 0;
                */
                
                rel(*this, left + right + below + above > 0);
                
                
                
                cout <<"I: " << i << ", Z: " << z <<endl;
                cout << "x[z]" << x[z] << " x[i]" << x[i] << " y[i]" << y[i] << " y[z]" << y[z] <<endl;
                cout << "left:" << left << "Right: " << right << " Below:" << below << " above: " << above << endl;
                
                
                
                
            }
        }
        
        
        branch(*this, x, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
        branch(*this, y, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
    }
    
    
    // cost function
    virtual IntVar cost(void) const {
        return s;
    }
    
    
    
    SquarePacking(bool share, SquarePacking& s) : Script(share, s) {
        x.update(*this, share, s.x);
        y.update(*this, share, s.y);
    }
    
    virtual Space* copy(bool share) {
        return new SquarePacking(share, *this);
    }
    
    
    //Print solution
    virtual void
    print(std::ostream& os) const {
        /*
         for (int i = 0; i < l.size(); i++) {
         os << l[i] << ", ";
         if ((i + 1) % 10 == 0)
         os << std::endl << "\t";
         }
         os << std::endl;
         */
        os << "X: " << x <<endl << "Y:" << y <<endl <<"S: " << s;
    }
};




int main(int argc, char* argv[]) {
    
    SizeOptions opt("SquarePacking");
    opt.size(6);
    
    
    //You can select different branchings, either from the predefined or specifing some other with a merit function
    //opt.branching(QueensN::NO_HEURISTIC);
    
    //opt.branching(QueensN::MAXIMIZE_ATTACKED_SQUARES_HEURISTIC);
    //opt.branching(QueensN::RANDOM_BRANCHING);
    //opt.branching(QueensN::KNIGHTS_MOVE_HEURISTIC);
    
    
    Script::run<SquarePacking, DFS, SizeOptions>(opt);
    
    
    return 0;
}

