#define LOGGER_CPP
#include <core/Logger.hpp>
#include <core/LogSink.hpp>
#include <utils/Active.hpp>

#include <vector>
#include <iostream>

namespace attpcfe {

  class Logger::LoggerImpl {

  public:
    LoggerImpl() {};

    std::vector<LogSink> _sinks;
    Active _active;
  };

  Logger::Logger() : _pImpl{new LoggerImpl{}, [](LoggerImpl* ptr){ delete ptr; }}
  {
    // Console sink
    addSink([](LogMsg::Meta const& meta, std::string const& msg){
	std::cout << meta._level
		  << "FILE: " << meta._file << ' '
		  << "LINE: " << meta._line << ' '
		  << "=> " << msg << '\n'; });
  }

  void Logger::addSink(LogSink sink) {

    _pImpl->_sinks.push_back(std::move(sink));
  }

  void Logger::flush(LogMsg const* msg) {

    auto meta = msg->_meta;
    auto msg_ = msg->_buffer.str();
    _pImpl->_active.send([=](){ for (auto const& sink : _pImpl->_sinks) log(sink, meta, msg_); });
  }

  LogMsg Logger::operator()(eLogLevel level, std::string const& filename, std::size_t line) {

    return LogMsg(this, level, filename, line);
  }
}
