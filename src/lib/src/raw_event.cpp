#define RAW_EVENT_CPP
#include <raw_event.hpp>
#include <pad.hpp>

#include <vector>

namespace attpcfe {

  class raw_event::raw_event_impl {

    std::vector<pad> _pads;

  public:
    raw_event_impl() {}
  };
    
  raw_event::raw_event() : _pimpl{new raw_event_impl{}, [](raw_event_impl* ptr){ delete ptr; }} {}
}
