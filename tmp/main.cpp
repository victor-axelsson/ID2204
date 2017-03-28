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



int main(int argc, const char * argv[]) {
    
    /*
    SendMoreMoney* m = new SendMoreMoney;
    Gecode::DFS<SendMoreMoney> e(m);
    delete m;
    
    while (SendMoreMoney* s = e.next()) {
        s->print(); delete s;
    }
     */
    
    SendMostMoney* m = new SendMostMoney;
    Gecode::BAB<SendMostMoney> e(m);
    delete m;
    
    while (SendMostMoney* s = e.next()) {
        s->print();
        delete s;
    }
    
    
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
