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

namespace attpcfe {

  PSATask::PSATask(std::shared_ptr<State> pState) : _pState{pState} {}

  void PSATask::Execute(MODE mode)
  {
    RawEvent rawEvent;
    _pState->PopRawEvent(rawEvent);

    Event event{rawEvent.Id(), rawEvent.NPads()};

    std::cout << "> run psa event: " << event.Id() << '\n';

    for (auto& pad : rawEvent.Pads())
    {
      if (mode == MODE::BLSUB)
      {
	BLCorrection blCorr;
	blCorr.SubtractBaseline(pad);
      }
      
      HitList hits;

      double charge = 1.0;
      std::vector<double> pos{0., 0., 0.};
      Hit hit{std::move(pos), charge};
      hits.AddHit(std::move(hit));
      
      event.AddHitList(std::move(hits));
    }
    _pState->PushEvent(std::move(event));
  }
  
}
