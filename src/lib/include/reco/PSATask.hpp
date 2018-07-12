#ifndef PSATASK_HPP
#define PSATASK_HPP

#include <memory>

namespace attpcfe
{
  class State;
  class PSATask {

    State* _pState;

  public:
    explicit PSATask(State* state);

    enum class MODE {
      BLSUB
    };

    void run(MODE mode);
  };
}
#endif
