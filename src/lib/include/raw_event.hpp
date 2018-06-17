#ifndef RAW_EVENT_HPP
#define RAW_EVENT_HPP

#include <memory>

namespace attpcfe {

  class raw_event {

    class raw_event_impl;
    std::unique_ptr<raw_event_impl, void(*)(raw_event_impl*)> _pimpl;

  public:
    raw_event();
  };
}
#endif
