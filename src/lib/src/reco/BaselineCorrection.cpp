#define BASELINECORRECTION_CPP
#include <reco/BaselineCorrection.hpp>
#include <core/RawEvent.hpp>
#include <core/Pad.hpp>

#include <iostream>
#include <algorithm>
#include <numeric>

namespace attpcfe {

  void BLCorrection::subtractBaseline(Pad& pad)
  {
    auto baseline = std::accumulate(std::next(std::begin(pad.rawData()), 500), std::end(pad.rawData()), 0.0) / 17;
    std::transform(std::next(std::begin(pad.rawData()), 5), std::end(pad.rawData()),
		   std::back_inserter(pad.data()),
		   [&baseline](int16_t rawAdc){ return static_cast<double>(rawAdc) - baseline; });
  }
  
}
