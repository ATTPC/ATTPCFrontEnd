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

  void HitList::AddHit(Hit&& h) { _pImpl->_hits.push_back(std::move(h)); }
}

