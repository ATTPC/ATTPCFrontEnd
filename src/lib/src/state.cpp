#define STATE_CPP
#include <state.hpp>
#include <stack.hpp>
#include <raw_event.hpp>
#include <event.hpp>

namespace attpcfe {

  class state::state_impl {

  public:
    state_impl() {}

    stack<raw_event> _raw_events;
    stack<event> _events;
  };

  state::state() : _pimpl{new state_impl{}, [](state_impl* ptr){ delete ptr; }} {}

  void state::reserve_stacks(std::size_t capacity)
  {
    _pimpl->_raw_events.reserve(capacity);
    _pimpl->_events.reserve(capacity);
  }

  void state::push_raw_event(raw_event&& evt) { _pimpl->_raw_events.push(std::move(evt)); }
  void state::pop_raw_event(raw_event& evt) { _pimpl->_raw_events.pop(evt); }
}
