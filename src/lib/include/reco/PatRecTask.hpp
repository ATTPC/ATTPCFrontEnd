#ifndef PATRECTASK_HPP
#define PATRECTASK_HPP

#include <memory>

namespace attpcfe
{
  class State;
  class PatRecTask {

    std::shared_ptr<State> _pState;

  public:
    PatRecTask(std::shared_ptr<State> pState);
 
    void Execute();
  };
}
#endif
