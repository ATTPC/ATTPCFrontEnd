#ifndef RECONSTRUCTIONTASKS_HPP
#define RECONSTRUCTIONTASKS_HPP

#include <memory>
#include <string>

namespace attpcfe {

  class ReconstructionDockState;
  class ReconstructionTask {

    class ReconstructionTaskImpl;
    std::unique_ptr<ReconstructionTaskImpl, void(*)(ReconstructionTaskImpl*)> _pImpl;
    
  public:
    ReconstructionTask(std::string file, ReconstructionDockState* state);
    void run();
  };
}
#endif
