#define PSATASK_CPP
#include <reco/PSATask.hpp>
#include <reco/BaselineCorrection.hpp>
#include <core/ReconstructionState.hpp>
#include <core/RawEvent.hpp>
#include <core/Pad.hpp>
#include <core/Event.hpp>
#include <core/HitList.hpp>
#include <core/Hit.hpp>
#include <core/Padplane.hpp>
#include <core/Tpc.hpp>

#include <iostream>
#include <algorithm>
#include <chrono>
using namespace std::chrono_literals;

namespace attpcfe {

  PSATask::PSATask(ReconstructionState* state) : _pState{state} {}

  void PSATask::run(MODE mode)
  {
    RawEvent rawEvent;
    _pState->popRawEvent(rawEvent);

    Event event{rawEvent.id(), rawEvent.nPads()};

    std::cout << "> run psa, event: " << event.id() << '\n';

    for (auto& pad : rawEvent.pads())
    {
      // Perform baseline subtraction 
      if (mode == MODE::BLSUB)
      {
	BLCorrection blCorr;
	blCorr.subtractBaseline(pad);
      }

      // Dummy for now, assuming a single hit par pad
      HitList hits;

      auto maxChargeBucket = std::max_element(std::begin(pad.data()), std::end(pad.data()));
      auto maxCharge = *maxChargeBucket;
      //auto timeBucket = _pState->tpc()->entryBucket() - std::distance(std::begin(pad.data()), maxChargeBucket);

      //if (maxCharge < 10) continue;

      std::cout << pad.number() << ' ' << maxCharge << ' ' << std::distance(std::begin(pad.data()), maxChargeBucket) << '\n';
      
      //auto pos = std::vector<double>{};
      //pos.emplace_back(_pState->padplane()->padCoords(pad.number()).first);
      //pos.emplace_back(_pState->padplane()->padCoords(pad.number()).second);
      //pos.emplace_back(0.); // z = 1000 - ((280 - timeBucket) * 80ns * 5.2 cm/us)
      
      //Hit hit{std::move(pos), maxCharge, pad.number()};
      //hits.addHit(std::move(hit));
      
      event.addHitList(std::move(hits));
    }
    _pState->pushEvent(std::move(event));
  }
  
}
