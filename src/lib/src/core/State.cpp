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

  void State::ReserveStacks(std::size_t capacity)
  {
    _pImpl->_rawEvents.Reserve(capacity);
    _pImpl->_events.Reserve(capacity);
  }

  void State::PushRawEvent(RawEvent&& evt) { _pImpl->_rawEvents.Push(std::move(evt)); }
  void State::PopRawEvent(RawEvent& evt) { _pImpl->_rawEvents.Pop(evt); }

  void State::PushEvent(Event&& evt) { _pImpl->_events.Push(std::move(evt)); }
  void State::PopEvent(Event& evt) { _pImpl->_events.Pop(evt); }

  void State::PushPatternEvent(PatternEvent&& evt) { _pImpl->_patternEvents.Push(std::move(evt)); }
  void State::PopPatternEvent(PatternEvent& evt) { _pImpl->_patternEvents.Pop(evt); }

  void State::PushTrackEvent(TrackEvent&& evt) { _pImpl->_trackEvents.Push(std::move(evt)); }
  void State::PopTrackEvent(TrackEvent& evt) { _pImpl->_trackEvents.Pop(evt); }
  std::size_t State::NTrackEvents() const { return _pImpl->_trackEvents.Size(); }
}
