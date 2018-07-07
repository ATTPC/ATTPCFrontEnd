#ifndef TRACKRECTASK_HPP
#define TRACKRECTASK_HPP

#include <memory>

namespace attpcfe
{
  class State;
  class TrackRecTask {

    std::shared_ptr<State> _pState;

  public:
    TrackRecTask(std::shared_ptr<State> pState);
 
    void Execute();
  };
}
#endif
