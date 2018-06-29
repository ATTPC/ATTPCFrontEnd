#define STATE_CPP
#include <state.hpp>
#include <stack.hpp>
#include <raw_event.hpp>
#include <event.hpp>
#include <pattern_event.hpp>
#include <track_event.hpp>

namespace attpcfe {

  class state::state_impl {

  public:
    state_impl() {}

    stack<raw_event> _raw_events;
    stack<event> _events;
    stack<pattern_event> _pattern_events;
    stack<track_event> _track_events;
  };

  state::state() : _pimpl{new state_impl{}, [](state_impl* ptr){ delete ptr; }} {}

  void state::reserve_stacks(std::size_t capacity)
  {
    _pimpl->_raw_events.reserve(capacity);
    _pimpl->_events.reserve(capacity);
  }

  void state::push_raw_event(raw_event&& evt) { _pimpl->_raw_events.push(std::move(evt)); }
  void state::pop_raw_event(raw_event& evt) { _pimpl->_raw_events.pop(evt); }

  void state::push_event(event&& evt) { _pimpl->_events.push(std::move(evt)); }
  void state::pop_event(event& evt) { _pimpl->_events.pop(evt); }

  void state::push_pattern_event(pattern_event&& evt) { _pimpl->_pattern_events.push(std::move(evt)); }
  void state::pop_pattern_event(pattern_event& evt) { _pimpl->_pattern_events.pop(evt); }

  void state::push_track_event(track_event&& evt) { _pimpl->_track_events.push(std::move(evt)); }
  void state::pop_track_event(track_event& evt) { _pimpl->_track_events.pop(evt); }
  std::size_t state::n_track_events() const { return _pimpl->_track_events.size(); }
}
