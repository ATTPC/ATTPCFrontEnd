#ifndef TRACKEVENT_HPP
#define TRACKEVENT_HPP

#include <memory>

namespace attpcfe {

  class Track;
  class TrackEvent {

    class TrackEventImpl;
    std::unique_ptr<TrackEventImpl, void(*)(TrackEventImpl*)> _pImpl;

  public:
    TrackEvent();
    explicit TrackEvent(std::size_t id);

    std::size_t id() const;
    void addTrack(Track&& track);
  };
}
#endif
