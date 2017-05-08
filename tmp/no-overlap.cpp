/*
 *  Main author:
 *     Christian Schulte <cschulte@kth.se>
 *
 *  Copyright:
 *     Christian Schulte, 2009
 *
 *  Permission is hereby granted, free of charge, to any person obtaining
 *  a copy of this software and associated documentation files (the
 *  "Software"), to deal in the Software without restriction, including
 *  without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to
 *  permit persons to whom the Software is furnished to do so, subject to
 *  the following conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 *  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 *  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include <gecode/int.hh>

using namespace Gecode;
using namespace Gecode::Int;

// The no-overlap propagator
class NoOverlap : public Propagator {
    
private:
    
    bool isSubsumed(){
        int n = x.size();
        for(int i = 0; i < n; i++){
            if(!x[i].assigned() || !y[i].assigned()){
                return false;
            }
        }
        return true;
    }
    
    int startFrom1(){
        //Here we ignore 1x1 you can also ignore 2x2 by returning a 2
        return 1;
    }
    
    bool overlaps(int i, int j, Space& home){
        
        
        bool left = x[j].gq(home, x[i].val() + w[i]);
        
                 
                 
        x[i].gq(home, x[j].min()+w[j]) == Int::ME_INT_FAILED &&
        x[j].gq(home, x[i].min()+w[i]) == Int::ME_INT_FAILED &&
        y[i].gq(home, y[j].min()+h[j]) == Int::ME_INT_FAILED &&
        y[j].gq(home, y[i].min()+h[i]) == Int::ME_INT_FAILED;
        
        
        return false;
    }
    
    
protected:
  // The x-coordinates
  ViewArray<IntView> x;
  // The width (array)
  int* w;
  // The y-coordinates
  ViewArray<IntView> y;
  // The heights (array)
  int* h;
public:
  // Create propagator and initialize
  NoOverlap(Home home, 
            ViewArray<IntView>& x0, int w0[], 
            ViewArray<IntView>& y0, int h0[])
    : Propagator(home), x(x0), w(w0), y(y0), h(h0) {
    x.subscribe(home,*this,PC_INT_BND);
    y.subscribe(home,*this,PC_INT_BND);
  }
  // Post no-overlap propagator
  static ExecStatus post(Home home, 
                         ViewArray<IntView>& x, int w[], 
                         ViewArray<IntView>& y, int h[]) {
    // Only if there is something to propagate
    if (x.size() > 1)
      (void) new (home) NoOverlap(home,x,w,y,h);
    return ES_OK;
  }

  // Copy constructor during cloning
  NoOverlap(Space& home, bool share, NoOverlap& p)
    : Propagator(home,share,p) {
    x.update(home,share,p.x);
    y.update(home,share,p.y);
    // Also copy width and height arrays
    w = home.alloc<int>(x.size());
    h = home.alloc<int>(y.size());
    for (int i=x.size(); i--; ) {
      w[i]=p.w[i]; h[i]=p.h[i];
    }
  }
  // Create copy during cloning
  virtual Propagator* copy(Space& home, bool share) {
    return new (home) NoOverlap(home,share,*this);
  }

  // Re-schedule function after propagator has been re-enabled
  virtual void reschedule(Space& home) {
     x.reschedule(home,*this,PC_INT_BND);
     y.reschedule(home,*this,PC_INT_BND);
  }

  // Return cost (defined as cheap quadratic)
  virtual PropCost cost(const Space&, const ModEventDelta&) const {
    return PropCost::quadratic(PropCost::LO,2*x.size());
  }
    

  // Perform propagation
  virtual ExecStatus propagate(Space& home, const ModEventDelta&) {

      //Check if subsumed
      if(isSubsumed()){
          return home.ES_SUBSUMED(* this);
      }
      

    
      int n = x.size();
    
      //Checkf for the overlaps
      for (int i = 0; i < n; i++) {
          for (int j = i + 1; j < n; j++) {
              
              //Check for overlap
              ModEvent left = x[j].gq(home, x[i].val() + w[i]);
              ModEvent right = x[i].gq(home, x[j].val() + w[j]);
              ModEvent above = y[j].gq(home, y[i].val() + h[i]);
              ModEvent below = y[i].gq(home, y[j].val() + h[j]);
              
              //Check for modifications
              if(me_modified(left) && me_modified(right) && me_modified(above) && me_modified(below)){
                  return ES_NOFIX;
              }

              //Check for fails
              if(me_failed(left) && me_failed(right) && me_failed(above) && me_failed(below)){
                  return ES_FAILED;
              }
          }
      }
      
      // Possible statuses
      //ExecStatus::ES_FIX
      //ExecStatus::ES_FAILED
      //ExecStatus::ES_NOFIX
      //ExecStatus::ES_NOFIX_FORCE
      //ExecStatus::ES_OK;
      
      return ES_FIX;
  }

  // Dispose propagator and return its size
  virtual size_t dispose(Space& home) {
    x.cancel(home,*this,PC_INT_BND);
    y.cancel(home,*this,PC_INT_BND);
    (void) Propagator::dispose(home);
    return sizeof(*this);
  }
};

/*
 * Post the constraint that the rectangles defined by the coordinates
 * x and y and width w and height h do not overlap.
 *
 * This is the function that you will call from your model. The best
 * is to paste the entire file into your model.
 */
void nooverlap(Home home, 
               const IntVarArgs& x, const IntArgs& w,
               const IntVarArgs& y, const IntArgs& h) {
  // Check whether the arguments make sense
  if ((x.size() != y.size()) || (x.size() != w.size()) ||
      (y.size() != h.size()))
    throw ArgumentSizeMismatch("nooverlap");
  // Never post a propagator in a failed space
  if (home.failed()) return;
  // Set up array of views for the coordinates
  ViewArray<IntView> vx(home,x);
  ViewArray<IntView> vy(home,y);
  // Set up arrays (allocated in home) for width and height and initialize
  int* wc = static_cast<Space&>(home).alloc<int>(x.size());
  int* hc = static_cast<Space&>(home).alloc<int>(y.size());
  for (int i=x.size(); i--; ) {
    wc[i]=w[i]; hc[i]=h[i];
  }
  // If posting failed, fail space
  if (NoOverlap::post(home,vx,wc,vy,hc) != ES_OK)
    home.fail();
}

