#ifndef TRACKRECTASK_HPP
#define TRACKRECTASK_HPP

#include <memory>

namespace attpcfe
{
  class State;
  class TrackRecTask {

    State* _pState;

  public:
    explicit TrackRecTask(State* pState);
 
    void run();
  };
}
#endif
