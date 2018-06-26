#define PATTERN_EVENT_CPP
#include <pattern_event.hpp>
#include <track.hpp>

#include <vector>

namespace attpcfe {

  class pattern_event::pattern_event_impl {

  public:
    pattern_event_impl() {};

    std::vector<track> _tracks;
  };

  pattern_event::pattern_event() : _pimpl{new pattern_event_impl{}, [](pattern_event_impl* ptr){ delete ptr; }} {}
}
