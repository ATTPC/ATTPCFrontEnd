#ifndef HIT_HPP
#define HIT_HPP

#include <memory>

namespace attpcfe {

  class hit {

    class hit_impl;
    std::unique_ptr<hit_impl, void(*)(hit_impl*)> _pimpl;

  public:
    hit();
  };
}
#endif
