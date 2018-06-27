#define TRACK_CPP
#include <track.hpp>

namespace attpcfe {

  class track::track_impl {

  public:
    track_impl() {}
  };

  track::track() : _pimpl{new track_impl{}, [](track_impl* ptr){ delete ptr; }} {}
}
