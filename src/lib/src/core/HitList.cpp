#define HITLIST_CPP
#include <core/HitList.hpp>
#include <core/Hit.hpp>

#include <vector>

namespace attpcfe {

  class HitList::HitListImpl {

  public:
    HitListImpl() {}

    std::vector<Hit> _hits;
  };

  HitList::HitList() : _pImpl{new HitListImpl{}, [](HitListImpl* ptr){ delete ptr; }} {}

  void HitList::addHit(Hit&& h) { _pImpl->_hits.push_back(std::move(h)); }

  std::size_t HitList::nHits() const { return _pImpl->_hits.size(); }
  std::vector<Hit> const& HitList::hits() const { return _pImpl->_hits; }
}

