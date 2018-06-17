#define EVENT_CPP
#include <event.hpp>

namespace attpcfe {

  class event::event_impl {

  public:
    event_impl() {}
  };
  
  event::event() : _pimpl{new event_impl{}, [](event_impl* ptr){ delete ptr; }} {}
}
