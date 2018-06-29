#ifndef RAW_TRACK_HPP
#define RAW_TRACK_HPP

#include <memory>

namespace attpcfe {

  class raw_track {

    class raw_track_impl;
    std::unique_ptr<raw_track_impl, void(*)(raw_track_impl*)> _pimpl;

  public:
    raw_track();
  };
}
#endif
