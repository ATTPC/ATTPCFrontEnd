#define LOGGER_CPP
#include <utils/Logger.hpp>
#include <utils/LogSink.hpp>
#include <utils/Active.hpp>

#include <vector>

namespace attpcfe {

  class Logger::LoggerImpl {

  public:
    LoggerImpl() {};

    Active _active;
    std::vector<LogSink> _sinks;
  };

  Logger::Logger() : _pImpl{new LoggerImpl{}, [](LoggerImpl* ptr){ delete ptr; }}
  {
    addSink(makeConsoleSink()); // Console sink.
    addSink(makeFileSink("/home/nico/Desktop/attpcfe.log")); // File sink.
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
    gLogDebug << "Run unit test on Logger" << std::endl;
    
    gLog << "Testing message log";
    gLogDebug << "Testing debug log";
    gLogWarning << "Testing warning log";
    gLogError << "Testing error log";
    gLogFatal << "Testing fatal log";
    gLogDebug << "Unit test done" << std::endl;
  }
#endif
}
