#ifndef RAWEVENT_HPP
#define RAWEVENT_HPP

#include <memory>
#include <vector>

namespace attpcfe {

  class Pad;
  class RawEvent {

    class RawEventImpl;
    std::unique_ptr<RawEventImpl, void(*)(RawEventImpl*)> _pImpl;

  public:
    RawEvent();
    RawEvent(std::size_t id, std::size_t nPads);

    std::size_t Id() const;
    std::size_t NPads() const;
    std::vector<Pad> const& Pads() const;
    std::vector<Pad>& Pads();
    void AddPad(Pad&& pad);
  };
}
#endif
