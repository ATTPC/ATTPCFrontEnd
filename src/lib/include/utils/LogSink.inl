#ifndef LOGSINK_INL
#define LOGSINK_INL

namespace attpcfe {

  // Here declare all non-friend non-member log functions
  template <typename T>
  void log(T const& sink, LogMsg::Meta const& meta, std::string const& msg) {

    sink(meta, msg);
  }

  // model_t
  template <typename T>
  LogSink::model_t<T>::model_t(T data) : _data{std::move(data)} {}

  //template <typename T>
  //std::unique_ptr<concept_t> LogSink::model_t<T>::copy_() const {

  //  return std::make_unique<model_t<T>>(*this);
  //}
  
  template <typename T>
  void LogSink::model_t<T>::log_(LogMsg::Meta const& meta, std::string const& msg) const {

    log(_data, meta, msg);
  }

  // wrapper
  template <typename T>
  LogSink::LogSink(T impl) : _self(std::make_shared<model_t<T>>(std::move(impl))) {}
  //LogSink::LogSink(T impl) : _self(std::make_unique<model_t<T>>(std::move(impl))) {}
}
#endif
