#define PSATASK_CPP
#include <reco/PSATask.hpp>
#include <reco/BaselineCorrection.hpp>
#include <core/State.hpp>
#include <core/RawEvent.hpp>
#include <core/Pad.hpp>
#include <core/Event.hpp>
#include <core/HitList.hpp>
#include <core/Hit.hpp>

#include <iostream>
#include <thread>
#include <chrono>
using namespace std::chrono_literals;

namespace attpcfe {

  PSATask::PSATask(State* state) : _pState{state} {}

  void PSATask::run(MODE mode)
  {
    RawEvent rawEvent;
    _pState->popRawEvent(rawEvent);

    Event event{rawEvent.id(), rawEvent.nPads()};

    std::cout << "> run psa, event: " << event.id() << '\n';

    for (auto& pad : rawEvent.pads())
    {
      if (mode == MODE::BLSUB)
      {
	BLCorrection blCorr;
	blCorr.subtractBaseline(pad);
      }
      
      HitList hits;

      double charge = 1.0;
      std::vector<double> pos{0., 0., 0.};
      Hit hit{std::move(pos), charge};
      hits.addHit(std::move(hit));
      
      event.addHitList(std::move(hits));
    }

    std::this_thread::sleep_for(0.001s);
    
    _pState->pushEvent(std::move(event));
  }
  
}
