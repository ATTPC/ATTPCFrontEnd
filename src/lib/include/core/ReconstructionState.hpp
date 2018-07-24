#ifndef RECONSTRUCTIONSTATE_HPP
#define RECONSTRUCTIONSTATE_HPP

#include <memory>

namespace attpcfe {

  template<typename T>
  class Stack;
  class Padplane;
  class Tpc;
  class RawEvent;
  class Event;
  class PatternEvent;
  class TrackEvent;
  class ReconstructionState {

    class ReconstructionStateImpl;
    std::unique_ptr<ReconstructionStateImpl, void(*)(ReconstructionStateImpl*)> _pImpl;
    
    //ReconstructionState();

  public:
    ReconstructionState();
    ReconstructionState(ReconstructionState const&) = delete;
    ReconstructionState& operator=(ReconstructionState const&) = delete;

    //static ReconstructionState& Instance() // Initialization of static local storage variable is thread-safe since C++11
    //{
    //static ReconstructionState _state;
    //return _state;
    //}

    void setPadplane(std::unique_ptr<Padplane> padplane);
    void setTpc(std::unique_ptr<Tpc> tpc);
    Padplane* padplane();
    Tpc* tpc();

    void reserveStacks(std::size_t capacity);
    void pushRawEvent(RawEvent&& evt);
    void popRawEvent(RawEvent& evt);
    void pushEvent(Event&& evt);
    void popEvent(Event& evt);
    void pushPatternEvent(PatternEvent&& evt);
    void popPatternEvent(PatternEvent& evt);
    void pushTrackEvent(TrackEvent&& evt);
    void popTrackEvent(TrackEvent& evt);

    Stack<Event> const& events() const;
    
    std::size_t nTrackEvents() const;
  };
}
#endif
