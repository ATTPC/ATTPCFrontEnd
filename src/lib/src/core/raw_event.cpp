#define RAW_EVENT_CPP
#include <raw_event.hpp>
#include <pad.hpp>

#include <vector>

namespace attpcfe {

  class raw_event::raw_event_impl {

  public:
    raw_event_impl() {}

    std::size_t _id;
    std::vector<pad> _pads;
  };

  raw_event::raw_event() : _pimpl{new raw_event_impl{}, [](raw_event_impl* ptr){ delete ptr; }} {}
  
  raw_event::raw_event(std::size_t id, std::size_t n_pads) : _pimpl{new raw_event_impl{}, [](raw_event_impl* ptr){ delete ptr; }}
  {
    _pimpl->_id = id;
    _pimpl->_pads.reserve(n_pads);
  }

  std::size_t raw_event::id() const { return _pimpl->_id; }
  std::size_t raw_event::n_pads() const { return _pimpl->_pads.size(); }
  std::vector<pad> const& raw_event::pads() const { return _pimpl->_pads; }
  void raw_event::add_pad(pad&& p)
  {
    _pimpl->_pads.push_back(std::move(p));
  }
}
