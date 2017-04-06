//
//  Fabric.cpp
//  tmp
//
//  Created by Victor Axelsson on 2017-04-03.
//  Copyright © 2017 simple_solutions. All rights reserved.
//

#include <stdio.h>
#include <gecode/int.hh>
#include <gecode/search.hh>
#include "Examples.cpp"
#include <gecode/minimodel.hh>



using namespace Gecode;
using namespace std;
const int NR_OF_ITEMS = 26;


class Fabric : public IntMinimizeSpace {
protected:
    IntVarArray xPos;
    IntVarArray yPos;
    IntVar lowestY;
    IntVar lowestX;
    int canvasWidth;
    int canvasHeight;
    
    
public:
    Fabric(int width, int height) : xPos(*this, NR_OF_ITEMS, 0, width), yPos(*this, NR_OF_ITEMS, 0, height), lowestY(*this, 0, height), lowestX(*this, 0, width) {
        
        canvasWidth = width;
        canvasHeight = height;
        
        cout << "Started" <<endl;
        
        IntArgs w(NR_OF_ITEMS);
        IntArgs h(NR_OF_ITEMS);
        
        for(int i = 0; i < NR_OF_ITEMS; i++){
            w[i] = fabric_examples_widths[i];
            h[i] = fabric_examples_heights[i];
            rel(*this, xPos[i], IRT_LQ, width - fabric_examples_widths[i]);
            rel(*this, yPos[i], IRT_GQ, fabric_examples_heights[i]);
        }
        
        nooverlap(*this, xPos, w, yPos, h);
        
        max(*this, yPos, lowestY);
        
        
        branch(*this, yPos, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
       // branch(*this, xPos, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
    }
    
    
    virtual void constrain(const Space& _b) {
        const Fabric& b = static_cast<const Fabric&>(_b);
        rel(*this, lowestY, IRT_LE, b.lowestY);
    }

    
    Fabric(bool share, Fabric& s) : IntMinimizeSpace(share, s) {
        xPos.update(*this, share, s.xPos);
        yPos.update(*this, share, s.yPos);
        lowestY.update(*this, share, s.lowestY);
        canvasWidth = s.canvasWidth;
        canvasHeight = s.canvasHeight;
    }
    
    virtual Space* copy(bool share) {
        return new Fabric(share, *this);
    }
    
    // cost function
    virtual IntVar cost(void) const {
        return lowestY;
    }
    
    
    void print(void) const {
        //convert -size 100x100 xc:none -fill red -draw 'rectangle 10,10 10,10' testing.jpg
        cout << "XPOS: " << xPos <<endl <<endl << "YPos: " << yPos <<endl << "---" <<endl <<endl;
        cout << "CMD: "<< endl << endl;
        
        cout << "convert -size " << canvasWidth << "x" << canvasHeight << " xc:none ";
        
        for(int i = 0; i < NR_OF_ITEMS; i++){
            
            int x1 = xPos[i].min();
            int y1 = canvasHeight - yPos[i].min();
            int x2 = xPos[i].min() + fabric_examples_widths[i];
            int y2 = canvasHeight - yPos[i].min() - fabric_examples_heights[i];
            
            cout << "  -fill "<< colors[i % 7] <<" -stroke black -draw \" rectangle " << x1 << "," << y1 <<" " << x2 <<"," << y2  << "\" ";
        }
        
        cout << " testing.jpg ";
        
    }
    
};