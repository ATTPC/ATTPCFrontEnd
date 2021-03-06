#ifndef EVENT_HPP
#define EVENT_HPP

#include <memory>
#include <vector>

namespace attpcfe {

  class HitList;
  class Event {

    class EventImpl;
    std::unique_ptr<EventImpl, void(*)(EventImpl*)> _pImpl;

  public:
    Event();
    Event(std::size_t id, std::size_t nHitLists);

    std::size_t id() const;
    std::size_t nHitLists() const;
    std::vector<HitList> const& hitLists() const;
    void addHitList(HitList&& list);
    void shrinkHitLists();
  };
}
#endif
