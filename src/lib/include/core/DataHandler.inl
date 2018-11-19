#ifndef DATAHANDLER_INL
#define DATAHANDLER_INL

namespace attpcfe {

  template<typename T>	
  DataHandler<T>::DataHandler() {}

  template<typename T>
  DataHandler<T>::~DataHandler() { close(); }

  template<typename T>		
  void DataHandler<T>::setDataFile(std::string const& file) { _dataFile = file; }

  template<typename T>		
  std::string const& DataHandler<T>::dataFile() const { return _dataFile; }

  template<typename T>	
  void DataHandler<T>::open(std::string const& file) { std::tie(_nRawEvents, _fRawEvent) = _T.open(file); }

  template<typename T>
  std::size_t DataHandler<T>::nRawEvents() const { return _nRawEvents; }

  template<typename T>
  std::size_t DataHandler<T>::fRawEvent() const { return _fRawEvent; }

  template<typename T>
  std::size_t DataHandler<T>::nPads(std::size_t iRawEvent) { return _T.nPads(iRawEvent); }

  template<typename T>
  std::vector<int16_t> DataHandler<T>::padRawData(std::size_t iPad) { return _T.padRawData(iPad); }

  template<typename T>
  void DataHandler<T>::endRawEvent() const { _T.endRawEvent(); }

  template<typename T>
  void DataHandler<T>::close() const { _T.close(); }
}
#endif
