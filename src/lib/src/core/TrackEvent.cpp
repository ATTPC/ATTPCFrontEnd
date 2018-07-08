#define TRACKEVENT_CPP
#include <core/TrackEvent.hpp>
#include <core/Track.hpp>

#include <vector>

namespace attpcfe {

  class TrackEvent::TrackEventImpl {

  public:
    TrackEventImpl() {};

    std::size_t _id;
    std::vector<Track> _tracks;
  };

  TrackEvent::TrackEvent() : _pImpl{new TrackEventImpl{}, [](TrackEventImpl* ptr){ delete ptr; }} {}

  TrackEvent::TrackEvent(std::size_t id) : _pImpl{new TrackEventImpl{}, [](TrackEventImpl* ptr){ delete ptr; }}
  {
    _pImpl->_id = id;
  }

  std::size_t TrackEvent::id() const { return _pImpl->_id; }

  void TrackEvent::addTrack(Track&& track) {
    
    _pImpl->_tracks.push_back(std::move(track));
  }
}
