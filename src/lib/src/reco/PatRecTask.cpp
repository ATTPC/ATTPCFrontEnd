#define PATRECTASK_CPP
#include <reco/PatRecTask.hpp>
#include <core/ReconstructionState.hpp>
#include <core/Event.hpp>
#include <core/PatternEvent.hpp>
#include <core/RawTrack.hpp>

#include <iostream>

#include <thread>
#include <chrono>
using namespace std::chrono_literals;

namespace attpcfe {

  PatRecTask::PatRecTask(ReconstructionState* state) : _pState{state} {}

  void PatRecTask::run()
  {
    Event event;
    _pState->popEvent(event);

    PatternEvent patternEvent{event.id()};

    std::cout << "> run pat rec, event: " << patternEvent.id() << '\n';

    RawTrack rawTrack;
    patternEvent.addRawTrack(std::move(rawTrack));

    std::this_thread::sleep_for(0.001s);
    
    _pState->pushPatternEvent(std::move(patternEvent));
  }
  
}
