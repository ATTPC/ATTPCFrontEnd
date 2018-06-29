#ifndef STATE_HPP
#define STATE_HPP

#include <memory>

namespace attpcfe {

  class raw_event;
  class event;
  class pattern_event;
  class track_event;
  class state {

    class state_impl;
    std::unique_ptr<state_impl, void(*)(state_impl*)> _pimpl;
    
    state();

  public:
    state(state const&) = delete;
    state& operator=(state const&) = delete;

    static state& instance() // Initialization of static local storage variable is thread-safe since C++11
    {
      static state _state;
      return _state;
    }

    void reserve_stacks(std::size_t capacity);
    void push_raw_event(raw_event&& evt);
    void pop_raw_event(raw_event& evt);
    void push_event(event&& evt);
    void pop_event(event& evt);
    void push_pattern_event(pattern_event&& evt);
    void pop_pattern_event(pattern_event& evt);
    void push_track_event(track_event&& evt);
    void pop_track_event(track_event& evt);
    std::size_t n_track_events() const;
  };
}
#endif
