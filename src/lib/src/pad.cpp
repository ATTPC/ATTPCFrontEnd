#define PAD_CPP
#include <pad.hpp>

#include <vector>

namespace attpcfe {

  class pad::pad_impl {

    std::vector<int> _adcs;

  public:
    pad_impl() {}
  };

  pad::pad() : _pimpl{new pad_impl{}, [](pad_impl* ptr){ delete ptr; }} {}
  
}
