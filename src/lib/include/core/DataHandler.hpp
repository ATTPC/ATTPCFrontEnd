#ifndef DATAHANDLER_HPP
#define DATAHANDLER_HPP

#include <cstddef>
#include <cstdint>
#include <vector>
#include <tuple>

namespace attpcfe {

  template<typename T>
  class DataHandler {

    T _T;
    std::string _dataFile;
    std::size_t _nRawEvents;
    std::size_t _fRawEvent;
    
  public:
    DataHandler();
    ~DataHandler();

    void setDataFile(std::string const& file);
    std::string const& dataFile() const;
    void open(std::string const& file);
    std::size_t nRawEvents() const;
    std::size_t fRawEvent() const;
    std::size_t nPads(std::size_t iRawEvent);
    std::vector<int16_t> padRawData(std::size_t iPad);
    void endRawEvent() const;
    void close() const;
  };
}

#include <core/DataHandler.inl>
#endif
