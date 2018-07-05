#ifndef TRACKEVENT_HPP
#define TRACKEVENT_HPP

#include <memory>

namespace attpcfe {

  class TrackEvent {

    class TrackEventImpl;
    std::unique_ptr<TrackEventImpl, void(*)(TrackEventImpl*)> _pImpl;

  public:
    TrackEvent();
    TrackEvent(std::size_t id);

    std::size_t Id() const;
  };
}
#endif
