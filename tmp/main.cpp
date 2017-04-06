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
#include "Sudoku.cpp"
#include "SendMostMoneyScript.hpp"
#include "Fabric.cpp"
#include <gecode/driver.hh>
#include <gecode/int.hh>
#include <gecode/minimodel.hh>


int main(int argc, char * argv[]) {
    
    /*
    SendMoreMoney* m = new SendMoreMoney;
    Gecode::DFS<SendMoreMoney> e(m);
    delete m;
    
    while (SendMoreMoney* s = e.next()) {
        s->print();
        delete s;
    }
     */
    
        /*
    Sudoku* m = new Sudoku;
    Gecode::DFS<Sudoku> e(m);
    delete m;
    
    while (Sudoku* s = e.next()) {
        s->print();
        delete s;
    }
         */
    
    
    Fabric* m = new Fabric(200, 1000);
    Gecode::BAB<Fabric> e(m);
    delete m;
    
    while (Fabric* s = e.next()) {
        s->print();
        delete s;
    }

    
    /*
    SendMostMoney* m = new SendMostMoney;
    Gecode::BAB<SendMostMoney> e(m);
    delete m;
    
    while (SendMostMoney* s = e.next()) {
        s->print();
        delete s;
    }
    
    
    // commandline options
    Options opt("SEND + MOST = MONEY");
    opt.model(SendMostMoneyScript::MODEL_SINGLE, "single", "use single linear equation");
    opt.model(SendMostMoneyScript::MODEL_CARRY, "carry", "use carry");
    opt.model(SendMostMoneyScript::MODEL_SINGLE);
    opt.solutions(0);
    opt.parse(argc, argv);
    // run script
    Script::run<SendMostMoneyScript,BAB,Options>(opt);
    */
    
    /*
    SendMoreMoney* m = new SendMoreMoney;
    Gist::Print<SendMoreMoney> p("Print solution");
    Gist::Options o;
    o.inspect.click(&p);
    Gist::dfs(m,o);
    delete m;
     */
    
    
    
    return 0;
    
}
