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
    ~DataHandler() { Close(); }

    void Open(char const* file) { _nRawEvents = _T.Open(file); }
    std::size_t NRawEvents() const { return _nRawEvents; }
    std::size_t NPads(std::size_t iRawEvent) { return _T.NPads(iRawEvent); }
    std::vector<int16_t> PadRawData(std::size_t iPad) { return _T.PadRawData(iPad); }
    void EndRawEvent() { _T.EndRawEvent(); }
    void Close() { _T.Close(); }
  };
}
#endif
