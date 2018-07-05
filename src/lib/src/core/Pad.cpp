#define PAD_CPP
#include <core/Pad.hpp>

namespace attpcfe {

  class Pad::PadImpl {

  public:
    PadImpl() {}

    std::vector<int16_t> _rawData;
  };

  Pad::Pad() : _pImpl{new PadImpl{}, [](PadImpl* ptr){ delete ptr; }} {}


  void Pad::SetRawData(std::vector<int16_t>&& data) { _pImpl->_rawData = std::move(data); }
  int16_t Pad::Cobo() const { return _pImpl->_rawData[0]; }
  
}
