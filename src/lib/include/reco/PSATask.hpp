#ifndef PSATASK_HPP
#define PSATASK_HPP

#include <memory>

namespace attpcfe
{
  class ReconstructionState;
  class PSATask {

    ReconstructionState* _pState;

  public:
    explicit PSATask(ReconstructionState* state);

    enum class MODE {
      BLSUB
    };

    void run(MODE mode);
  };
}
#endif
