#ifndef HITLIST_HPP
#define HITLIST_HPP

#include <memory>
#include <vector>

namespace attpcfe {

  class Hit;
  class HitList {

    class HitListImpl;
    std::unique_ptr<HitListImpl, void(*)(HitListImpl*)> _pImpl;

  public:
    HitList();

    void addHit(Hit&& h);
    std::size_t nHits() const;
    std::vector<Hit> const& hits() const;
  };
}
#endif
