#ifndef HITLIST_HPP
#define HITLIST_HPP

#include <memory>

namespace attpcfe {

  class Hit;
  class HitList {

    class HitListImpl;
    std::unique_ptr<HitListImpl, void(*)(HitListImpl*)> _pImpl;

  public:
    HitList();

    void AddHit(Hit&& h);
  };
}
#endif
