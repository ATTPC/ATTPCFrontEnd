#define EVENT_CPP
#include <event.hpp>
#include <hit_list.hpp>

#include <vector>

namespace attpcfe {

  class event::event_impl {

  public:
    event_impl() {}

    std::vector<hit_list> _hit_lists;
  };
  
  event::event() : _pimpl{new event_impl{}, [](event_impl* ptr){ delete ptr; }} {}

  event::event(std::size_t n_hit_lists) : _pimpl{new event_impl{}, [](event_impl* ptr){ delete ptr; }}
  {
    _pimpl->_hit_lists.reserve(n_hit_lists);
  }
}
