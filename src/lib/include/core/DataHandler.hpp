#ifndef DATAHANDLER_HPP
#define DATAHANDLER_HPP

#include <cstddef>
#include <cstdint>
#include <vector>

namespace attpcfe {

  template<typename T>
  class DataHandler {

    T _T;
    std::size_t _nRawEvents;
    
  public:
    DataHandler() {}
    ~DataHandler() { close(); }

    void open(char const* file) { _nRawEvents = _T.open(file); }
    std::size_t nRawEvents() const { return _nRawEvents; }
    std::size_t nPads(std::size_t iRawEvent) { return _T.nPads(iRawEvent); }
    std::vector<int16_t> padRawData(std::size_t iPad) { return _T.padRawData(iPad); }
    void endRawEvent() { _T.endRawEvent(); }
    void close() { _T.close(); }
  };
}
#endif
