#define TRACKRECTASK_CPP
#include <reco/TrackRecTask.hpp>
#include <core/State.hpp>
#include <core/PatternEvent.hpp>
#include <core/TrackEvent.hpp>
#include <core/Track.hpp>

#include <iostream>

#include <thread>
#include <chrono>
using namespace std::chrono_literals;

namespace attpcfe {

  TrackRecTask::TrackRecTask(std::shared_ptr<State> pState) : _pState{pState} {}

  void TrackRecTask::Execute()
  {
    PatternEvent patternEvent;
    _pState->PopPatternEvent(patternEvent);

    TrackEvent trackEvent{patternEvent.Id()};

    std::cout << "> run track rec, event: " << trackEvent.Id() << '\n';

    Track track;
    trackEvent.AddTrack(std::move(track));

    std::this_thread::sleep_for(0.001s);
    
    _pState->PushTrackEvent(std::move(trackEvent));
  }
  
}
