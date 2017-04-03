//
//  SendMostMoneyScript.hpp
//  tmp
//
//  Created by Victor Axelsson on 2017-03-28.
//  Copyright © 2017 simple_solutions. All rights reserved.
//

#ifndef SendMostMoneyScript_hpp
#define SendMostMoneyScript_hpp

#include <stdio.h>
//
//  SendMostMoney.hpp
//  tmp
//
//  Created by Victor Axelsson on 2017-03-28.
//  Copyright © 2017 simple_solutions. All rights reserved.
//
#include <gecode/driver.hh>
#include <gecode/int.hh> 
#include <gecode/minimodel.hh>

using namespace Gecode;

class SendMostMoneyScript : public IntMaximizeScript{
protected:
    IntVarArray l;
    IntVar money;
public:
    enum {
        MODEL_SINGLE, MODEL_CARRY
    };
    
    SendMostMoneyScript(const Options& opt) : IntMaximizeScript(opt), l(*this, 8, 0, 9), money(*this, 0, 100000){
        IntVar s(l[0]), e(l[1]), n(l[2]), d(l[3]), m(l[4]), o(l[5]), t(l[6]), y(l[7]);
        
        rel(*this, s != 0);
        rel(*this, m != 0);
        distinct(*this, l);
        //rel(*this, 1000*s + 100*e + 10*n + d + 1000*m + 100*o + 10*s + t == 10000*m + 1000*o + 100*n + 10*e + y);
        //rel(*this, money == 10000*m + 1000*o + 100*n + 10*e + y);
        
        switch (opt.model()) {
            case MODEL_SINGLE:
                rel(*this, 1000*s + 100*e + 10*n + d + 1000*m + 100*o + 10*s + t == 10000*m + 1000*o + 100*n + 10*e + y);
                break;
            case MODEL_CARRY:
                
                // using carries
                {
                    IntVar c0(*this, 0, 1), c1(*this, 0, 1), c2(*this, 0, 1), c3(*this, 0, 1);
                
                    rel(*this, d + t == y + 10 * c0);
                    rel(*this, c0 + n + s == e + 10 * c1);
                    rel(*this, c1 + e + o == n + 10 * c2);
                    rel(*this, c2 + s + m == o + 10 * c3);
                    rel(*this, c3 == m);
                }
        
                break;
        }
        
        rel(*this, money == 10000*m + 1000*o + 100*n + 10*e + y);
        
        branch(*this, l, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
    }
    
    SendMostMoneyScript(bool share, SendMostMoneyScript& s) : IntMaximizeScript(share, s){
        l.update(*this, share, s.l);
        money.update(*this, share, s.money);
    }
    
    virtual Space* copy(bool share){
        return new SendMostMoneyScript(share, *this);
    }
    
    void print(void) const {
        std::cout << l << std::endl;
    }
    
    virtual void print(std::ostream& os) const {
        os << l << std::endl;
    }
    
    // cost function
    virtual IntVar cost(void) const {
        return money;
    }
};


#endif /* SendMostMoneyScript_hpp */
