#define TRACK_CPP
#include <core/Track.hpp>

namespace attpcfe {

  class Track::TrackImpl {

  public:
    TrackImpl() {}
  };

  Track::Track() : _pImpl{new TrackImpl{}, [](TrackImpl* ptr){ delete ptr; }} {}
}
