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
    std::size_t nPads(std::size_t iRawEvent) const;
    std::vector<int16_t> padRawData(std::size_t iPad) const;
    void endRawEvent() const;
    void close() const;
    /*
    DataHandler() {}
    ~DataHandler() { close(); }

    void setDataFile(std::string const& file) { _dataFile = file; }
    std::string const& dataFile() const { return _dataFile; } 
    void open(std::string const& file) { std::tie(_nRawEvents, _fRawEvent) = _T.open(file); }
    std::size_t nRawEvents() const { return _nRawEvents; }
    std::size_t fRawEvent() const { return _fRawEvent; }
    std::size_t nPads(std::size_t iRawEvent) { return _T.nPads(iRawEvent); }
    std::vector<int16_t> padRawData(std::size_t iPad) { return _T.padRawData(iPad); }
    void endRawEvent() { _T.endRawEvent(); }
    void close() { _T.close(); }
    */
  };
}
#endif
