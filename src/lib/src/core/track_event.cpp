#define TRACK_EVENT_CPP
#include <track_event.hpp>
#include <track.hpp>

#include <vector>

namespace attpcfe {

  class track_event::track_event_impl {

  public:
    track_event_impl() {};

    std::size_t _id;
    std::vector<track> _tracks;
  };

  track_event::track_event() : _pimpl{new track_event_impl{}, [](track_event_impl* ptr){ delete ptr; }} {}

  track_event::track_event(std::size_t id) : _pimpl{new track_event_impl{}, [](track_event_impl* ptr){ delete ptr; }}
  {
    _pimpl->_id = id;
  }

  std::size_t track_event::id() const { return _pimpl->_id; }
}
