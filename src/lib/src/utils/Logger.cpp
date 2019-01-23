#define LOGGER_CPP
#include <utils/Logger.hpp>
#include <utils/LogSink.hpp>
#include <utils/Active.hpp>

#include <vector>

#include <iostream>

namespace attpcfe {

  class Logger::LoggerImpl {

  public:
    LoggerImpl() {};

    Active _active;
    std::vector<LogSink> _sinks;
  };

  Logger::Logger() : _pImpl{new LoggerImpl{}, [](LoggerImpl* ptr){ delete ptr; }}
  {
    // Console sink.
    addSink(makeConsoleSink());
    // File sink.
    addSink(makeFileSink("/home/nico/Desktop/attpcfe.log"));
  }

  void Logger::addSink(LogSink sink) {

    _pImpl->_sinks.push_back(std::move(sink));
  }

  void Logger::flush(LogMsg const* msg) {

    auto meta = msg->_meta;
    auto msg_ = msg->_buffer.str();
    _pImpl->_active.send([=](){	for (auto const& sink : _pImpl->_sinks) log(sink, meta, msg_); });
  }

  LogMsg Logger::operator()(eLogLevel level, std::string const& filename, std::size_t line) {

    return LogMsg(this, level, filename, line);
  }

#ifdef UNITTEST
  void Logger::test()
  {
    std::cout << "> Logger::test\n";
  }
#endif
}
