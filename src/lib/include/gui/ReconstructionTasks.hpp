#ifndef RECONSTRUCTIONTASKS_HPP
#define RECONSTRUCTIONTASKS_HPP

#include <memory>
#include <string>

namespace attpcfe {

  class ReconstructionTask {

    class ReconstructionTaskImpl;
    std::unique_ptr<ReconstructionTaskImpl, void(*)(ReconstructionTaskImpl*)> _pImpl;
    
  public:
    ReconstructionTask();
    void run();
  };
}
#endif
