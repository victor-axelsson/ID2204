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
#include "Examples.cpp"

using namespace Gecode;
using namespace std;


class SquarePacking :  public Script {
    
private:
    static int size(int i, int n){
        //[0, 1, 2, 3, 4, 5] == index
        //[6, 5, 4, 3, 2, 1] == size from n
        return n - i;
    }
    
protected:
    IntVarArray x;
    IntVarArray y;
    IntVar s;
    int n;
    
public:
    
    SquarePacking(const SizeOptions& opt): Script(opt){
        n = opt.size();

        x = IntVarArray(*this, opt.size() , 0, opt.size());
        y = IntVarArray(*this, opt.size() , 0, opt.size());
        s = IntVar(*this, 0, opt.size() + opt.size() -1);
        
        
        //Make sure the x and y are within the boundries of s
        for(int i = 0; i < n; i++){
            int xW = size(i, n);
            
            rel(*this, x[i], IRT_LQ, LinIntExpr(s - x[i] + xW).post(*this, IPL_VAL));
            rel(*this, y[i], IRT_LQ, LinIntExpr(s - y[i] + xW).post(*this, IPL_VAL));
        }
        
        
        //No overlap
        for(int i = 0; i < n; i++){
            int iSize = size(i, n);
            
            for(int z = i + 1; z < n; z++){
                int zSize = size(z, n);

                
                //If x[i] is:
                BoolVar left(*this, 0, 1);
                BoolVar right(*this, 0, 1);
                BoolVar above(*this, 0, 1);
                BoolVar below(*this, 0, 1);
                
                rel(*this, x[z], IRT_GQ, LinIntExpr(x[i] + iSize).post(*this, IPL_VAL), left);
                rel(*this, x[i], IRT_GQ, LinIntExpr(x[z] + zSize).post(*this, IPL_VAL), right);
                rel(*this, y[i], IRT_GQ, LinIntExpr(y[z] + zSize).post(*this, IPL_VAL), below);
                rel(*this, y[z], IRT_GQ, LinIntExpr(y[i] + iSize).post(*this, IPL_VAL), above);
                
                
                rel(*this, left + right + below + above > 0);
                
                cout <<"I: " << i << ", Z: " << z <<endl;
                //cout << "x[z]" << x[z] << " x[i]" << x[i] << " y[i]" << y[i] << " y[z]" << y[z] <<endl;
                //cout << "Left:" << left << " Right:" << right << " Below:" << below << " Above:" << above << endl << endl;
                
            }
        }
        
        //Column sum
        
        
        branch(*this, s,  INT_VAL_MIN());
        branch(*this, x, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
        branch(*this, y, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
    }
    
    
    // cost function
    virtual IntVar cost(void) const {
        return s;
    }
    
    
    SquarePacking(bool share, SquarePacking& tmp) : Script(share, tmp) {
        x.update(*this, share, tmp.x);
        y.update(*this, share, tmp.y);
        s.update(*this, share, tmp.s);
        n = tmp.n;
    }
    
    virtual Space* copy(bool share) {
        return new SquarePacking(share, *this);
    }
    
    
    //Print solution
    virtual void
    print(std::ostream& os) const {
        
        cout << "convert -size " << 11 << "x" << 11 << " xc:none ";
        
        for(int i = 0; i < n; i++){
            
            int x1 = x[i].min();
            int y1 = y[i].min();
            int x2 = x[i].min() + size(i, n) -1;
            int y2 = y[i].min() + size(i, n) -1;
            
            if(size(i, n) == 1){
                cout << "  -fill "<< colors[i % 7] <<" -draw \" color " << x1 << "," << y1 << " point " << "\" ";
            }else{
                cout << "  -fill "<< colors[i % 7] <<" -draw \" rectangle " << x1 << "," << y1 <<" " << x2 <<"," << y2  << "\" ";
            }
        }
        
        cout << " -scale 600% squares.jpg ";
        
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

