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

  std::size_t RawEvent::Id() const { return _pImpl->_id; }
  std::size_t RawEvent::NPads() const { return _pImpl->_pads.size(); }
  std::vector<Pad> const& RawEvent::Pads() const { return _pImpl->_pads; }
  void RawEvent::AddPad(Pad&& p)
  {
    _pImpl->_pads.push_back(std::move(p));
  }
}
