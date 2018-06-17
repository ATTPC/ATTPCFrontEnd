#ifndef STATE_HPP
#define STATE_HPP

#include <memory>

namespace attpcfe {

  class state {

    class state_impl;
    std::unique_ptr<state_impl, void(*)(state_impl*)> _pimpl;
    
    state();

  public:
    state(state const&) = delete;
    state& operator=(state const&) = delete;

    static state& instance()
    {
      static state _state;
      return _state;
    }
  };
}
#endif
