#define PAD_CPP
#include <core/Pad.hpp>

namespace attpcfe {

  class Pad::PadImpl {

  public:
    PadImpl() {}

    std::vector<int16_t> _rawData;
    std::vector<double> _data;
  };

  Pad::Pad() : _pImpl{new PadImpl{}, [](PadImpl* ptr){ delete ptr; }}
  {
    _pImpl->_rawData.reserve(517);
    _pImpl->_data.reserve(512);
  }

  void Pad::setRawData(std::vector<int16_t> data) { _pImpl->_rawData = std::move(data); }
  std::vector<double>& Pad::data() { return _pImpl->_data; }

  std::vector<int16_t> const& Pad::rawData() const { return _pImpl->_rawData; }
  int16_t Pad::cobo() const { return _pImpl->_rawData[0]; }
  int16_t Pad::asad() const { return _pImpl->_rawData[1]; }
  int16_t Pad::aget() const { return _pImpl->_rawData[2]; }
  int16_t Pad::channel() const { return _pImpl->_rawData[3]; }
  int16_t Pad::number() const { return _pImpl->_rawData[4]; }
}
