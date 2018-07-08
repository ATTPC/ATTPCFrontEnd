#ifndef PATTERNEVENT_HPP
#define PATTERNEVENT_HPP

#include <memory>

namespace attpcfe {

  class RawTrack;
  class PatternEvent {

    class PatternEventImpl;
    std::unique_ptr<PatternEventImpl, void(*)(PatternEventImpl*)> _pImpl;

  public:
    PatternEvent();
    PatternEvent(std::size_t id);
    
    std::size_t id() const;
    void addRawTrack(RawTrack&& rawTrack);
  };
}
#endif
