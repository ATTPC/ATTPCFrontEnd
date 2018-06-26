#ifndef PATTERN_EVENT_HPP
#define PATTERN_EVENT_HPP

#include <memory>

namespace attpcfe {

  class pattern_event {

    class pattern_event_impl;
    std::unique_ptr<pattern_event_impl, void(*)(pattern_event_impl*)> _pimpl;

  public:
    pattern_event();
  };
}
#endif
