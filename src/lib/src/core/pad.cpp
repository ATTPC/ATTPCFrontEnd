#define PAD_CPP
#include <pad.hpp>

namespace attpcfe {

  class pad::pad_impl {

  public:
    pad_impl() {}

    std::vector<int16_t> _raw_data;
  };

  pad::pad() : _pimpl{new pad_impl{}, [](pad_impl* ptr){ delete ptr; }} {}


  void pad::set_raw_data(std::vector<int16_t>&& data) { _pimpl->_raw_data = std::move(data); }
  int16_t pad::cobo() const { return _pimpl->_raw_data[0]; }
  
}
