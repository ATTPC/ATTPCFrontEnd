#define TRACK_CPP
#include <core/RawTrack.hpp>
#include <core/Hit.hpp>

#include <vector>

namespace attpcfe {

  class RawTrack::RawTrackImpl {

  public:
    RawTrackImpl() {}

    std::vector<Hit> _hits;
  };

  RawTrack::RawTrack() : _pImpl{new RawTrackImpl{}, [](RawTrackImpl* ptr){ delete ptr; }} {}
}
