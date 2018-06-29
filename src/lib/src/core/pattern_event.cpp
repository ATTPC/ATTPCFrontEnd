#define PATTERN_EVENT_CPP
#include <pattern_event.hpp>
#include <raw_track.hpp>

#include <vector>

namespace attpcfe {

  class pattern_event::pattern_event_impl {

  public:
    pattern_event_impl() {};

    std::size_t _id;
    std::vector<raw_track> _raw_tracks;
  };

  pattern_event::pattern_event() : _pimpl{new pattern_event_impl{}, [](pattern_event_impl* ptr){ delete ptr; }} {}

  pattern_event::pattern_event(std::size_t id) : _pimpl{new pattern_event_impl{}, [](pattern_event_impl* ptr){ delete ptr; }}
  {
    _pimpl->_id = id;
  }

  std::size_t pattern_event::id() const { return _pimpl->_id; }
}
