#ifndef PAD_HPP
#define PAD_HPP

#include <memory>

namespace attpcfe {

  class pad {

    class pad_impl;
    std::unique_ptr<pad_impl, void(*)(pad_impl*)> _pimpl;

  public:
    pad();
  };
}
#endif
