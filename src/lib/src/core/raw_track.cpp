#define TRACK_CPP
#include <raw_track.hpp>
#include <hit.hpp>

#include <vector>

namespace attpcfe {

  class raw_track::raw_track_impl {

  public:
    raw_track_impl() {}

    std::vector<hit> _hits;
  };

  raw_track::raw_track() : _pimpl{new raw_track_impl{}, [](raw_track_impl* ptr){ delete ptr; }} {}
}
