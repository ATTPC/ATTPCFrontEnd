#define LOGGER_CPP
#include <core/Logger.hpp>
#include <utils/Active.h>

#include <vector>

namespace attpcfe {

  class Logger::LoggerImpl {

  public:
    LoggerImpl() = default;

    //std::vector<LogSink> _sinks;
    Active _active;
  };

  Logger::Logger() : _pImpl{new LoggerImpl{}, [](LoggerImpl* ptr){ delete ptr; }} {}
}
