#ifndef RECONSTRUCTIONTASKS_HPP
#define RECONSTRUCTIONTASKS_HPP

#include <memory>
#include <string>

namespace attpcfe {

  template<typename T>
  class DataHandler;
  class Hdf5Wrapper;
  class ReconstructionDockState;
  class ReconstructionTask {

    class ReconstructionTaskImpl;
    std::unique_ptr<ReconstructionTaskImpl, void(*)(ReconstructionTaskImpl*)> _pImpl;
    
  public:
    ReconstructionTask(DataHandler<Hdf5Wrapper>* pDataHandler, std::size_t fromEvent, std::size_t nEvents, ReconstructionDockState* pState);
    void run();
  };
}
#endif
