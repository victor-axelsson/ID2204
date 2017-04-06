//
//  main.cpp
//  tmp
//
//  Created by Victor Axelsson on 2017-03-28.
//  Copyright © 2017 simple_solutions. All rights reserved.
//

#include <iostream>
#include <gecode/int.hh>
#include <gecode/search.hh>
#include <gecode/gist.hh>
#include "SendMoreMoney.hpp"
#include "SendMostMoney.hpp"
#include "queensN.cpp"
#include "SendMostMoneyScript.hpp"
#include "Fabric.cpp"
#include <gecode/driver.hh>
#include <gecode/int.hh>
#include <gecode/minimodel.hh>


int main(int argc, char * argv[]) {
       
        
    QueensN* m = new QueensN;
    Gecode::DFS<QueensN> e(m);
    delete m;
    
    while (QueensN* s = e.next()) {
        s->print();
        delete s;
    }
         
    
    
    return 0;
    
}