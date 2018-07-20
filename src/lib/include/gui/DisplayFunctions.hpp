#ifndef DISPLAYFUNCTIONS_HPP
#define DISPLAYFUNCTIONS_HPP

namespace attpcfe {

  class Display;
  class Padplane;
  class Tpc;
  
  void display(Display* display, Padplane* padplane);
  void display(Display* display, Tpc* tpc);
}
#endif
