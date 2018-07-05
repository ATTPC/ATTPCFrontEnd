#ifndef HIT_HPP
#define HIT_HPP

#include <memory>
#include <vector>

namespace attpcfe {

  class Hit {

    class HitImpl;
    std::unique_ptr<HitImpl, void(*)(HitImpl*)> _pImpl;

  public:
    Hit(std::vector<double>&& pos, double charge);
  };
}
#endif
