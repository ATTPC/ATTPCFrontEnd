#define STATE_CPP
#include <state.hpp>
#include <stack.hpp>
#include <raw_event.hpp>
#include <event.hpp>

namespace attpcfe {

  class state::state_impl {

    stack<raw_event> _raw_events;
    stack<event> _events;

  public:
    state_impl() {}
    
  };

  state::state() : _pimpl{new state_impl{}, [](state_impl* ptr){ delete ptr; }} {}
}
