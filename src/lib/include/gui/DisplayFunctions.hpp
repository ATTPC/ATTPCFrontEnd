#ifndef DISPLAYFUNCTIONS_HPP
#define DISPLAYFUNCTIONS_HPP

namespace attpcfe {

  class Display;
  class Padplane;
  class Tpc;
  class Event;
  
  void display(Display* display, Padplane* padplane);
  void display(Display* display, Tpc* tpc);
  void display(Display* display, Event const& event);
}
#endif
