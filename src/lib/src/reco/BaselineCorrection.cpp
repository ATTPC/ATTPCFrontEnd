#define BASELINECORRECTION_CPP
#include <reco/BaselineCorrection.hpp>
//#include <core/State.hpp>
#include <core/RawEvent.hpp>
#include <core/Pad.hpp>

#include <iostream>
#include <algorithm>
#include <numeric>

//#include <fstream>
//#include <iterator>

namespace attpcfe {

  void BLCorrection::SubtractBaseline(Pad& pad)
  {
    auto baseline = std::accumulate(std::next(std::begin(pad.RawData()), 500), std::end(pad.RawData()), 0.0) / 17;
    std::transform(std::next(std::begin(pad.RawData()), 5), std::end(pad.RawData()),
		   std::back_inserter(pad.Data()),
		   [&baseline](int16_t rawAdc){ return static_cast<double>(rawAdc) - baseline; });

    //std::ofstream out("baseline_sub.txt");
    //for (std::size_t i = 0; i < 512; ++i)
    //{
    //  out << i << ' ' << pad.RawData()[i + 5] << ' ' << pad.Data()[i] << '\n';
    //}
  }
  
}
