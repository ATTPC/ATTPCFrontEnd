#ifndef STATE_HPP
#define STATE_HPP

#include <memory>

namespace attpcfe {

  class RawEvent;
  class Event;
  class PatternEvent;
  class TrackEvent;
  class State {

    class StateImpl;
    std::unique_ptr<StateImpl, void(*)(StateImpl*)> _pImpl;
    
    //State();

  public:
    State();
    State(State const&) = delete;
    State& operator=(State const&) = delete;

    //static State& Instance() // Initialization of static local storage variable is thread-safe since C++11
    //{
    //static State _state;
    //return _state;
    //}

    void reserveStacks(std::size_t capacity);
    void pushRawEvent(RawEvent&& evt);
    void popRawEvent(RawEvent& evt);
    void pushEvent(Event&& evt);
    void popEvent(Event& evt);
    void pushPatternEvent(PatternEvent&& evt);
    void popPatternEvent(PatternEvent& evt);
    void pushTrackEvent(TrackEvent&& evt);
    void popTrackEvent(TrackEvent& evt);
    std::size_t nTrackEvents() const;
  };
}
#endif
