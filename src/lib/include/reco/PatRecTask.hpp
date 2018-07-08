#ifndef PATRECTASK_HPP
#define PATRECTASK_HPP

#include <memory>

namespace attpcfe
{
  class State;
  class PatRecTask {

    State* _pState;

  public:
    PatRecTask(State* state);
 
    void run();
  };
}
#endif
