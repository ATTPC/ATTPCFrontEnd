#ifndef TRACK_EVENT_HPP
#define TRACK_EVENT_HPP

#include <memory>

namespace attpcfe {

  class track_event {

    class track_event_impl;
    std::unique_ptr<track_event_impl, void(*)(track_event_impl*)> _pimpl;

  public:
    track_event();
    track_event(std::size_t id);

    std::size_t id() const;
  };
}
#endif
