#ifndef TRACKRECTASK_HPP
#define TRACKRECTASK_HPP

#include <memory>

namespace attpcfe
{
  class ReconstructionState;
  class TrackRecTask {

    ReconstructionState* _pState;

  public:
    explicit TrackRecTask(ReconstructionState* pState);
 
    void run();
  };
}
#endif
