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

  void Pad::SetRawData(std::vector<int16_t> data) { _pImpl->_rawData = std::move(data); }
  std::vector<double>& Pad::Data() { return _pImpl->_data; }

  std::vector<int16_t> const& Pad::RawData() const { return _pImpl->_rawData; }
  int16_t Pad::Cobo() const { return _pImpl->_rawData[0]; }
  int16_t Pad::Asad() const { return _pImpl->_rawData[1]; }
  int16_t Pad::Aget() const { return _pImpl->_rawData[2]; }
  int16_t Pad::Channel() const { return _pImpl->_rawData[3]; }
  int16_t Pad::Number() const { return _pImpl->_rawData[4]; }
}
