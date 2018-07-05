#ifndef EVENT_HPP
#define EVENT_HPP

#include <memory>

namespace attpcfe {

  class HitList;
  class Event {

    class EventImpl;
    std::unique_ptr<EventImpl, void(*)(EventImpl*)> _pImpl;

  public:
    Event();
    Event(std::size_t id, std::size_t nHitLists);

    std::size_t Id() const;
    std::size_t NHitLists() const;
    void AddHitList(HitList&& list);
  };
}
#endif
