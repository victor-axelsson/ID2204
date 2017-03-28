//
//  SendMostMoney.hpp
//  tmp
//
//  Created by Victor Axelsson on 2017-03-28.
//  Copyright © 2017 simple_solutions. All rights reserved.
//

#ifndef SendMostMoney_hpp
#define SendMostMoney_hpp

#include <stdio.h>
#include <gecode/int.hh>
#include <gecode/minimodel.hh>
#include <gecode/search.hh>

using namespace Gecode;

class SendMostMoney : public IntMaximizeSpace{
protected:
    IntVarArray l;
    IntVar money;
public:
    SendMostMoney(void) : l(*this, 8, 0, 9), money(*this, 0, 100000){
        IntVar s(l[0]), e(l[1]), n(l[2]), d(l[3]), m(l[4]), o(l[5]), t(l[6]), y(l[7]);
        
        rel(*this, s != 0);
        rel(*this, m != 0);
        distinct(*this, l);
        rel(*this, 1000*s + 100*e + 10*n + d + 1000*m + 100*o + 10*s + t == 10000*m + 1000*o + 100*n + 10*e + y);
        rel(*this, money == 10000*m + 1000*o + 100*n + 10*e + y);
        
        branch(*this, l, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
    }
    
    SendMostMoney(bool share, SendMostMoney& s) : IntMaximizeSpace(share, s){
        l.update(*this, share, s.l);
        money.update(*this, share, s.money);
    }
    
    virtual Space* copy(bool share){
        return new SendMostMoney(share, *this);
    }
    
    void print(void) const {
        std::cout << l << std::endl;
    }
    // cost function
    virtual IntVar cost(void) const {
        return money;
    }
};

#endif /* SendMostMoney_hpp */
