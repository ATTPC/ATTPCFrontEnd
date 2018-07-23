#ifndef RECONSTRUCTIONDOCKSTATE_HPP
#define RECONSTRUCTIONDOCKSTATE_HPP

#include <memory>

namespace attpcfe {

  class ReconstructionState;
  class ReconstructionDockState {

    class ReconstructionDockStateImpl;
    std::unique_ptr<ReconstructionDockStateImpl, void(*)(ReconstructionDockStateImpl*)> _pImpl;
    
    //ReconstructionState();

  public:
    ReconstructionDockState();
    ReconstructionDockState(ReconstructionDockState const&) = delete;
    ReconstructionDockState& operator=(ReconstructionDockState const&) = delete;

    ReconstructionState* state();
  };
}
#endif
