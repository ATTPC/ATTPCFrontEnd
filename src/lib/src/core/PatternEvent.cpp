#define PATTERNEVENT_CPP
#include <core/PatternEvent.hpp>
#include <core/RawTrack.hpp>

#include <vector>

namespace attpcfe {

  class PatternEvent::PatternEventImpl {

  public:
    PatternEventImpl() {};

    std::size_t _id;
    std::vector<RawTrack> _rawTracks;
  };

  PatternEvent::PatternEvent() : _pImpl{new PatternEventImpl{}, [](PatternEventImpl* ptr){ delete ptr; }} {}

  PatternEvent::PatternEvent(std::size_t id) : _pImpl{new PatternEventImpl{}, [](PatternEventImpl* ptr){ delete ptr; }}
  {
    _pImpl->_id = id;
  }

  std::size_t PatternEvent::id() const { return _pImpl->_id; }

  void PatternEvent::addRawTrack(RawTrack&& rawTrack) {

    _pImpl->_rawTracks.push_back(std::move(rawTrack));
  }
}
