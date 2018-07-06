#define BASELINECORRECTION_CPP
#include <reco/BaselineCorrection.hpp>
#include <core/State.hpp>
#include <core/RawEvent.hpp>
#include <core/Pad.hpp>

#include <iostream>

namespace attpcfe {

  BLCorrection::BLCorrection(std::shared_ptr<State> pState) : _pState{pState} {}

  void BLCorrection::SubtractBaseline()
  {
    RawEvent rawEvent;
    _pState->PopRawEvent(rawEvent);

    std::cout << rawEvent.Id() << '\n';
    //std::cout << rawEvent.Pads()[0].Cobo() << '\n';
  }
}
