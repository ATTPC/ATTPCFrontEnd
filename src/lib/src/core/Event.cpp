#define EVENT_CPP
#include <core/Event.hpp>
#include <core/HitList.hpp>

#include <vector>

namespace attpcfe {

  class Event::EventImpl {

  public:
    EventImpl() {}

    std::size_t _id;
    std::vector<HitList> _hitLists;
  };
  
  Event::Event() : _pImpl{new EventImpl{}, [](EventImpl* ptr){ delete ptr; }} {}

  Event::Event(std::size_t id, std::size_t nHitLists) : _pImpl{new EventImpl{}, [](EventImpl* ptr){ delete ptr; }}
  {
    _pImpl->_id = id;
    _pImpl->_hitLists.reserve(nHitLists);
  }

  std::size_t Event::id() const { return _pImpl->_id; }
  std::size_t Event::nHitLists() const { return _pImpl->_hitLists.size(); }
  void Event::addHitList(HitList&& list)
  {
    _pImpl->_hitLists.push_back(std::move(list));
  }
}
