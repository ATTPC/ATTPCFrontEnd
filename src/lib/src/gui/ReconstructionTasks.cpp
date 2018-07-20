#define RECONSTRUCTIONTASKS_CPP
#include <gui/ReconstructionTasks.hpp>

namespace attpcfe {

  class ReconstructionTask::ReconstructionTaskImpl {

  public:
    ReconstructionTaskImpl() {}
  };

  ReconstructionTask::ReconstructionTask() :
    _pImpl{new ReconstructionTaskImpl{}, [](ReconstructionTaskImpl* ptr){ delete ptr; }} {}
  
  void ReconstructionTask::run()
  {

  }
}
