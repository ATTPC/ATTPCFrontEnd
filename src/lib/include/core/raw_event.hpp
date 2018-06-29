#ifndef RAW_EVENT_HPP
#define RAW_EVENT_HPP

#include <memory>
#include <vector>

namespace attpcfe {

  class pad;
  class raw_event {

    class raw_event_impl;
    std::unique_ptr<raw_event_impl, void(*)(raw_event_impl*)> _pimpl;

  public:
    raw_event();
    raw_event(std::size_t id, std::size_t n_pads);

    std::size_t id() const;
    std::size_t n_pads() const;
    std::vector<pad> const& pads() const;
    void add_pad(pad&& pad);
  };
}
#endif
