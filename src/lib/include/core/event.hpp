#ifndef EVENT_HPP
#define EVENT_HPP

#include <memory>

namespace attpcfe {

  class hit_list;
  class event {

    class event_impl;
    std::unique_ptr<event_impl, void(*)(event_impl*)> _pimpl;

  public:
    event();
    event(std::size_t id, std::size_t n_hit_lists);

    std::size_t id() const;
    std::size_t n_hit_lists() const;
    void add_hit_list(hit_list&& list);
  };
}
#endif
