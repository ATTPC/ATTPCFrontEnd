#ifndef HIT_HPP
#define HIT_HPP

#include <memory>
#include <vector>

namespace attpcfe {

  class hit {

    class hit_impl;
    std::unique_ptr<hit_impl, void(*)(hit_impl*)> _pimpl;

  public:
    hit(std::vector<double>&& pos, double charge);
  };
}
#endif
