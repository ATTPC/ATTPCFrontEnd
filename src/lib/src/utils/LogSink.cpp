#define LOGSINK_CPP
#include <utils/LogSink.hpp>
#include <utils/LogMsg.hpp>

namespace attpcfe {

  //LogSink::LogSink(LogSink const& logSink) : _self(logSink._self->copy_()) {}

  //LogSink& LogSink::operator=(LogSink const& logSink) {

  //  return *this = LogSink(logSink);
  //}

  void log(LogSink const& sink, LogMsg::Meta const& meta, std::string const& msg) { sink._self->log_(meta, msg); }
}
