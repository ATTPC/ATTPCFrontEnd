#ifndef EVENT_HPP
#define EVENT_HPP

#include <memory>

namespace attpcfe {

  class event {

    class event_impl;
    std::unique_ptr<event_impl, void(*)(event_impl*)> _pimpl;

  public:
    event();
    event(std::size_t n_hit_lists);
  };
}
#endif
