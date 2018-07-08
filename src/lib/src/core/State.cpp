#define STATE_CPP
#include <core/State.hpp>
#include <core/Stack.hpp>
#include <core/RawEvent.hpp>
#include <core/Event.hpp>
#include <core/PatternEvent.hpp>
#include <core/TrackEvent.hpp>

namespace attpcfe {

  class State::StateImpl {

  public:
    StateImpl() {}

    Stack<RawEvent> _rawEvents;
    Stack<Event> _events;
    Stack<PatternEvent> _patternEvents;
    Stack<TrackEvent> _trackEvents;
  };

  State::State() : _pImpl{new StateImpl{}, [](StateImpl* ptr){ delete ptr; }} {}

  void State::reserveStacks(std::size_t capacity)
  {
    _pImpl->_rawEvents.reserve(capacity);
    _pImpl->_events.reserve(capacity);
  }

  void State::pushRawEvent(RawEvent&& evt) { _pImpl->_rawEvents.push(std::move(evt)); }
  void State::popRawEvent(RawEvent& evt) { _pImpl->_rawEvents.pop(evt); }

  void State::pushEvent(Event&& evt) { _pImpl->_events.push(std::move(evt)); }
  void State::popEvent(Event& evt) { _pImpl->_events.pop(evt); }

  void State::pushPatternEvent(PatternEvent&& evt) { _pImpl->_patternEvents.push(std::move(evt)); }
  void State::popPatternEvent(PatternEvent& evt) { _pImpl->_patternEvents.pop(evt); }

  void State::pushTrackEvent(TrackEvent&& evt) { _pImpl->_trackEvents.push(std::move(evt)); }
  void State::popTrackEvent(TrackEvent& evt) { _pImpl->_trackEvents.pop(evt); }
  std::size_t State::nTrackEvents() const { return _pImpl->_trackEvents.size(); }
}
