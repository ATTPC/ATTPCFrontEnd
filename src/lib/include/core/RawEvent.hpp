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

    std::size_t id() const;
    std::size_t nPads() const;
    std::vector<Pad> const& pads() const;
    std::vector<Pad>& pads();
    void addPad(Pad&& pad);
  };
}
#endif
