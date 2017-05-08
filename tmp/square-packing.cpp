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
#include <string>


#include "no-overlap.cpp"

using namespace Gecode;
using namespace std;



namespace custom {
	/*
	* Post the constraint that the rectangles defined by the coordinates
	* x and y and width w and height h do not overlap.
	*
	* This is the function that you will call from your model. The best
	* is to paste the entire file into your model.
	*/

	void custom_nooverlap(Home home,
		const IntVarArgs& x, const IntArgs& w,
		const IntVarArgs& y, const IntArgs& h) {
		// Check whether the arguments make sense
		if ((x.size() != y.size()) || (x.size() != w.size()) ||
			(y.size() != h.size()))
			throw ArgumentSizeMismatch("nooverlap");
		// Never post a propagator in a failed space
		if (home.failed()) return;
		// Set up array of views for the coordinates
		ViewArray<IntView> vx(home, x);
		ViewArray<IntView> vy(home, y);
		// Set up arrays (allocated in home) for width and height and initialize
		int* wc = static_cast<Space&>(home).alloc<int>(x.size());
		int* hc = static_cast<Space&>(home).alloc<int>(y.size());
		for (int i = x.size(); i--; ) {
			wc[i] = w[i]; hc[i] = h[i];
		}
		// If posting failed, fail space
		if (NoOverlap::post(home, vx, wc, vy, hc) != ES_OK)
			home.fail();
	}

}
//Just some colors for printing with ImageMagic
static const string colors[] = {"red", "green", "silver", "blue", "yellow", "brown", "gray", "white"};

class SquarePacking :  public Script {
    
private:
    
    
    static int size(int i, int n){
        //[0, 1, 2, 3, 4, 5] == index
        //[6, 5, 4, 3, 2, 1] == size from n
        return n - i;
    }
    
    int startFrom1(){
        //Here we ignore 1x1 you can also ignore 2x2 by returning a 2
        return 1;
    }
    
    int getGaps(int i ){
        
        //Start with the specifica cases
        if(i == 3){
            return 3;
        }else if(i == 2){
            return 2;
        }else{
            
            //Generic ones
            if (i==45){
                return 10;
            } else if (i >=34){
                return 9;
            } else if (i >=30){
                return 8;
            }else if (i >= 22){
                return 7;
            }else if ( i >= 18){
                return 6;
            }else if (i >= 12){
                return 5;
            }else if (i >= 9){
                return 4;
            }else if (i >= 5){
                return 3;
            }else if (i >= 2){
                return 2;
            }else{
                return -1;
            }
        }
        
        return -1;
    }
    
    
protected:
    IntVarArray x;
    IntVarArray y;
    IntVar s;
    int n;
    
    int maxOfs(){
        return n * ceil(sqrt(n));
    }
    
    int minOfs(){
        return ceil(sqrt(n * (n + 1) * (2 * n + 1) / 6));
    }
    
public:

    enum{
        BRANCHING_ASSIGN_X_THEN_Y,
        BRANCHING_BIGGER_SQUARES_FIRST,
        BRANCHING_LEFT_TO_RIGHT,
        BRANCHING_TOP_TO_BOTTOM,
        BRANCHING_RAND
    };
    
    enum{
        PROPAGATION_REIFIED,
        PROPAGATION_CUSTOM
    };

    
    SquarePacking(const SizeOptions& opt): Script(opt){

        n = opt.size();
          
        x = IntVarArray(*this, opt.size() , 0, maxOfs());
        y = IntVarArray(*this, opt.size() , 0, maxOfs());
        //s = IntVar(*this, 0, maxOfs());
        
        s = IntVar(*this, minOfs(), maxOfs());

        //Make sure the x and y are within the boundries of s
        for(int i = 0; i < n - startFrom1(); i++){
            int xW = size(i, n);
            
            rel(*this, x[i], IRT_LQ, LinIntExpr(s - x[i] + xW).post(*this, IPL_VAL));
            rel(*this, y[i], IRT_LQ, LinIntExpr(s - y[i] + xW).post(*this, IPL_VAL));
        }
        
        if(opt.model() == PROPAGATION_REIFIED){
        
    
            //No overlap, reification
            for(int i = 0; i < n - startFrom1(); i++){
                int iSize = size(i, n);
                
                for(int z = i + 1; z < n - startFrom1(); z++){
                    int zSize = size(z, n);
                    
                    
                    //If x[i] is to the:
                    BoolVar left(*this, 0, 1);
                    BoolVar right(*this, 0, 1);
                    BoolVar above(*this, 0, 1);
                    BoolVar below(*this, 0, 1);
                    
                    //Check the separate reifications
                    rel(*this, x[z], IRT_GQ, LinIntExpr(x[i] + iSize).post(*this, IPL_VAL), left);
                    rel(*this, x[i], IRT_GQ, LinIntExpr(x[z] + zSize).post(*this, IPL_VAL), right);
                    rel(*this, y[i], IRT_GQ, LinIntExpr(y[z] + zSize).post(*this, IPL_VAL), below);
                    rel(*this, y[z], IRT_GQ, LinIntExpr(y[i] + iSize).post(*this, IPL_VAL), above);
                    
                    //Al least on of these should apply
                    rel(*this, left + right + below + above > 0);
                    
                    //cout <<"I: " << i << ", Z: " << z <<endl;
                    //cout << "x[z]" << x[z] << " x[i]" << x[i] << " y[i]" << y[i] << " y[z]" << y[z] <<endl;
                    //cout << "Left:" << left << " Right:" << right << " Below:" << below << " Above:" << above << endl << endl;
                    
                }
            }
        }else if(opt.model() == PROPAGATION_CUSTOM){
            
            
            IntArgs w(n), h(n);
            for (int i = 0; i < n; ++i) {
                w[i] = size(i, n);
                h[i] = size(i, n);
            }

			custom::custom_nooverlap(*this, x, w, y, h);
             
        }
        
        
        //Part 3, Column and row constraints
        for(int c = 0; c < maxOfs(); c++){
            
            //Create bool vars for columns and rows
            BoolVarArray colsMatch(*this, n, 0, 1);
            BoolVarArray rowsMatch(*this, n, 0, 1);
            
            for (int i=0; i < n - startFrom1() ; i++){
                int iSize = size(i, n);
                
                //Apply the domain contstraints for rows and columns
                dom(*this, x[i], c - iSize +1, c, colsMatch[i]);
                dom(*this, y[i], c - iSize +1, c, rowsMatch[i]);
            }
            
            //Sum them up and see that they all don't overfit the row or cols
            rel(*this, sum(IntArgs::create(n, n, -1), colsMatch) <= s);
            rel(*this, sum(IntArgs::create(n, n, -1), rowsMatch) <= s);
        }
        
        //Remove symmetry
        rel(*this, x[0] <= (s - n) / 2);
        rel(*this, y[0] <= x[0]);
        
        //Empty strip dominance
        for(int i = 0; i < n - startFrom1(); i++){
            int gap = getGaps(i);
            
            //Check if within boundry
            if (size(i, n) <= 45 || size(i, n) >= 2){
                rel(*this, x[i] != gap);
                rel(*this, y[i] != gap);
            }
        }
        
        // Do branching
        //Apply branching on s first
        branch(*this, s,  INT_VAL_MIN());
        
        /*
         ***** available branchings *****
         BRANCHING_ASSIGN_X_THEN_Y,
         BRANCHING_BIGGER_SQUARES_FIRST,
         BRANCHING_LEFT_TO_RIGHT,
         BRANCHING_TOP_TO_BOTTOM,
         BRANCHING_RAND
         */
        if(opt.branching() == BRANCHING_ASSIGN_X_THEN_Y){
            branch(*this, x, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
            branch(*this, y, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
        }else if(opt.branching() == BRANCHING_BIGGER_SQUARES_FIRST){
            for(int i = 0; i < n - startFrom1(); i++){
                branch(*this, x[i], INT_VAL_MIN());
                branch(*this, y[i], INT_VAL_MIN());
            }
        
        }else if(opt.branching() == BRANCHING_LEFT_TO_RIGHT){
            branch(*this, x, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
            branch(*this, y, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
        }else if(opt.branching() == BRANCHING_TOP_TO_BOTTOM){
            branch(*this, y, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
            branch(*this, x, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
        }else if(opt.branching() == BRANCHING_RAND){
            branch(*this, x, INT_VAR_RND(0), INT_VAL_MIN());
            branch(*this, y, INT_VAR_RND(0), INT_VAL_MIN());
        }
        
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
        
        cout << "convert -size " << n + n -1 << "x" << n + n -1 << " xc:none ";
        
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
    opt.size(7);
    opt.branching(SquarePacking::BRANCHING_LEFT_TO_RIGHT);
    opt.model(SquarePacking::PROPAGATION_CUSTOM);
    
    
    /*
    opt.branching(SquarePacking::BRANCHING_ASSIGN_X_THEN_Y);
    opt.branching(SquarePacking::BRANCHING_BIGGER_SQUARES_FIRST);
    opt.branching(SquarePacking::BRANCHING_LEFT_TO_RIGHT);
    opt.branching(SquarePacking::BRANCHING_TOP_TO_BOTTOM);
     opt.branching(SquarePacking::BRANCHING_RAND);
    */
    
    

    
    Script::run<SquarePacking, BAB, SizeOptions>(opt);

    return 0;
}