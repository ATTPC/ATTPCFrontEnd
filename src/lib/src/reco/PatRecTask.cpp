#define PATRECTASK_CPP
#include <reco/PatRecTask.hpp>
#include <core/State.hpp>
#include <core/Event.hpp>
#include <core/PatternEvent.hpp>
#include <core/RawTrack.hpp>

#include <iostream>

#include <thread>
#include <chrono>
using namespace std::chrono_literals;

namespace attpcfe {

  PatRecTask::PatRecTask(std::shared_ptr<State> pState) : _pState{pState} {}

  void PatRecTask::Execute()
  {
    Event event;
    _pState->PopEvent(event);

    PatternEvent patternEvent{event.Id()};

    std::cout << "> run pat rec, event: " << patternEvent.Id() << '\n';

    RawTrack rawTrack;
    patternEvent.AddRawTrack(std::move(rawTrack));

    std::this_thread::sleep_for(0.001s);
    
    _pState->PushPatternEvent(std::move(patternEvent));
  }
  
}
