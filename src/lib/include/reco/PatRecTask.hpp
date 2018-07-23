#ifndef PATRECTASK_HPP
#define PATRECTASK_HPP

#include <memory>

namespace attpcfe
{
  class ReconstructionState;
  class PatRecTask {

    ReconstructionState* _pState;

  public:
    explicit PatRecTask(ReconstructionState* state);
 
    void run();
  };
}
#endif
