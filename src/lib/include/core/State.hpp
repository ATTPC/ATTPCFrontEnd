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
    
    State();

  public:
    State(State const&) = delete;
    State& operator=(State const&) = delete;

    static State& Instance() // Initialization of static local storage variable is thread-safe since C++11
    {
      static State _state;
      return _state;
    }

    void ReserveStacks(std::size_t capacity);
    void PushRawEvent(RawEvent&& evt);
    void PopRawEvent(RawEvent& evt);
    void PushEvent(Event&& evt);
    void PopEvent(Event& evt);
    void PushPatternEvent(PatternEvent&& evt);
    void PopPatternEvent(PatternEvent& evt);
    void PushTrackEvent(TrackEvent&& evt);
    void PopTrackEvent(TrackEvent& evt);
    std::size_t NTrackEvents() const;
  };
}
#endif
