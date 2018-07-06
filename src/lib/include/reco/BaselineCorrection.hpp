#ifndef BASELINECORRECTION_HPP
#define BASELINECORRECTION_HPP

#include <memory>

namespace attpcfe
{
  class State;
  class BLCorrection {

    std::shared_ptr<State> _pState;

  public:
    BLCorrection(std::shared_ptr<State> pState);
    
    void SubtractBaseline();
  };
}
#endif
