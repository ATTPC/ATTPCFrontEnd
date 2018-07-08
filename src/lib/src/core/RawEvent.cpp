#define RAWEVENT_CPP
#include <core/RawEvent.hpp>
#include <core/Pad.hpp>

#include <vector>

namespace attpcfe {

  class RawEvent::RawEventImpl {

  public:
    RawEventImpl() {}

    std::size_t _id;
    std::vector<Pad> _pads;
  };

  RawEvent::RawEvent() : _pImpl{new RawEventImpl{}, [](RawEventImpl* ptr){ delete ptr; }} {}
  
  RawEvent::RawEvent(std::size_t id, std::size_t nPads) : _pImpl{new RawEventImpl{}, [](RawEventImpl* ptr){ delete ptr; }}
  {
    _pImpl->_id = id;
    _pImpl->_pads.reserve(nPads);
  }

  std::size_t RawEvent::id() const { return _pImpl->_id; }
  std::size_t RawEvent::nPads() const { return _pImpl->_pads.size(); }
  std::vector<Pad> const& RawEvent::pads() const { return _pImpl->_pads; }
  std::vector<Pad>& RawEvent::pads() { return _pImpl->_pads; }
  void RawEvent::addPad(Pad&& p)
  {
    _pImpl->_pads.push_back(std::move(p));
  }
}
