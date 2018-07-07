#ifndef PSATASK_HPP
#define PSATASK_HPP

#include <memory>

namespace attpcfe
{
  class State;
  class PSATask {

    std::shared_ptr<State> _pState;

  public:
    PSATask(std::shared_ptr<State> pState);
    enum class MODE {
      BLSUB
    };
    void Execute(MODE mode);
  };
}
#endif
