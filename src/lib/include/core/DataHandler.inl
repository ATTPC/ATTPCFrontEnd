#ifndef DATAHANDLER_INL
#define DATAHANDLER_INL

#include <core/DataHandler.hpp>

namespace attpcfe {

  template<typename T>	
  DataHandler::DataHandler() {}

  template<typename T>
  DataHandler::~DataHandler() { close(); }

  template<typename T>		
  void DataHandler::setDataFile(std::string const& file) const { _dataFile = file; }

  template<typename T>		
  std::string const& DataHandler::dataFile() const { return _dataFile; }

  template<typename T>	
  void DataHandler::open(std::string const& file) { std::tie(_nRawEvents, _fRawEvent) = _T.open(file); }

  template<typename T>
  std::size_t DataHandler::nRawEvents() const { return _nRawEvents; }

  template<typename T>
  std::size_t DataHandler::fRawEvent() const { return _fRawEvent; }

  template<typename T>
  std::size_t DataHandler::nPads(std::size_t iRawEvent) const { return _T.nPads(iRawEvent); }

  template<typename T>
  std::vector<int16_t> DataHandler::padRawData(std::size_t iPad) const { return _T.padRawData(iPad); }

  template<typename T>
  void DataHandler::endRawEvent() const { _T.endRawEvent(); }

  template<typename T>
  void DataHandler::close() const { _T.close(); }
}
#endif
