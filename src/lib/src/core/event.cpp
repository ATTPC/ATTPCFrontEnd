#define EVENT_CPP
#include <event.hpp>
#include <hit_list.hpp>

#include <vector>

namespace attpcfe {

  class event::event_impl {

  public:
    event_impl() {}

    std::size_t _id;
    std::vector<hit_list> _hit_lists;
  };
  
  event::event() : _pimpl{new event_impl{}, [](event_impl* ptr){ delete ptr; }} {}

  event::event(std::size_t id, std::size_t n_hit_lists) : _pimpl{new event_impl{}, [](event_impl* ptr){ delete ptr; }}
  {
    _pimpl->_id = id;
    _pimpl->_hit_lists.reserve(n_hit_lists);
  }

  std::size_t event::id() const { return _pimpl->_id; }
  std::size_t event::n_hit_lists() const { return _pimpl->_hit_lists.size(); }
  void event::add_hit_list(hit_list&& list)
  {
    _pimpl->_hit_lists.push_back(std::move(list));
  }
}
