#define RECONSTRUCTIONDOCKSTATE_CPP
#include <gui/ReconstructionDockState.hpp>
#include <core/ReconstructionState.hpp>

namespace attpcfe {

  class ReconstructionDockState::ReconstructionDockStateImpl {

  public:
    ReconstructionDockStateImpl() {}

    std::unique_ptr<ReconstructionState> _pState{std::make_unique<ReconstructionState>()};
  };

  ReconstructionDockState::ReconstructionDockState() : _pImpl{new ReconstructionDockStateImpl{}, [](ReconstructionDockStateImpl* ptr){ delete ptr; }} {}

  ReconstructionState* ReconstructionDockState::state() { return _pImpl->_pState.get(); }


}
