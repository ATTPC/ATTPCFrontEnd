#ifndef DATA_HANDLER_HPP
#define DATA_HANDLER_HPP

#include <cstddef>
#include <cstdint>
#include <vector>

namespace attpcfe {

  template<typename T>
  class data_handler {

    T _T;
    std::size_t _n_raw_events;
    
  public:
    data_handler() {}
    ~data_handler() { _T.close(); }

    void open(char const* file) { _n_raw_events = _T.open(file); }
    std::size_t n_raw_events() const { return _n_raw_events; }
    std::size_t n_pads(std::size_t i_raw_event) { return _T.n_pads(i_raw_event); }
    std::vector<int16_t> pad_raw_data(std::size_t i_pad) { return _T.pad_raw_data(i_pad); }
    void end_raw_event() { _T.end_raw_event(); }
    void close() { _T.close(); }
  };
}
#endif
