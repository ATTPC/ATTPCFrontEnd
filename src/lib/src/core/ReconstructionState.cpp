#define RECONSTRUCTIONSTATE_CPP
#include <core/ReconstructionState.hpp>
#include <core/Stack.hpp>
#include <core/RawEvent.hpp>
#include <core/Event.hpp>
#include <core/PatternEvent.hpp>
#include <core/TrackEvent.hpp>
#include <core/Padplane.hpp>
#include <core/Tpc.hpp>

namespace attpcfe {

  class ReconstructionState::ReconstructionStateImpl {

  public:
    ReconstructionStateImpl() {}

    std::unique_ptr<Padplane> _pPadplane;
    std::unique_ptr<Tpc> _pTpc;
    
    Stack<RawEvent> _rawEvents;
    Stack<Event> _events;
    Stack<PatternEvent> _patternEvents;
    Stack<TrackEvent> _trackEvents;
  };

  ReconstructionState::ReconstructionState() : _pImpl{new ReconstructionStateImpl{}, [](ReconstructionStateImpl* ptr){ delete ptr; }} {}
  
  void ReconstructionState::setPadplane(std::unique_ptr<Padplane> padplane) { _pImpl->_pPadplane = std::move(padplane); }
  void ReconstructionState::setTpc(std::unique_ptr<Tpc> tpc) { _pImpl->_pTpc = std::move(tpc); }
  Padplane* ReconstructionState::padplane() { return _pImpl->_pPadplane.get(); }
  Tpc* ReconstructionState::tpc() { return _pImpl->_pTpc.get(); }
  
  void ReconstructionState::reserveStacks(std::size_t capacity)
  {
    _pImpl->_rawEvents.reserve(capacity);
    _pImpl->_events.reserve(capacity);
  }

  void ReconstructionState::pushRawEvent(RawEvent&& evt) { _pImpl->_rawEvents.push(std::move(evt)); }
  void ReconstructionState::popRawEvent(RawEvent& evt) { _pImpl->_rawEvents.pop(evt); }
  void ReconstructionState::pushEvent(Event&& evt) { _pImpl->_events.push(std::move(evt)); }
  void ReconstructionState::popEvent(Event& evt) { _pImpl->_events.pop(evt); }
  void ReconstructionState::pushPatternEvent(PatternEvent&& evt) { _pImpl->_patternEvents.push(std::move(evt)); }
  void ReconstructionState::popPatternEvent(PatternEvent& evt) { _pImpl->_patternEvents.pop(evt); }
  void ReconstructionState::pushTrackEvent(TrackEvent&& evt) { _pImpl->_trackEvents.push(std::move(evt)); }
  void ReconstructionState::popTrackEvent(TrackEvent& evt) { _pImpl->_trackEvents.pop(evt); }

  Stack<Event> const& ReconstructionState::events() const { return _pImpl->_events; }

  std::size_t ReconstructionState::nTrackEvents() const { return _pImpl->_trackEvents.size(); }
}
