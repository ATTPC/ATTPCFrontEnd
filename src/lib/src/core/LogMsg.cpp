#define LOGMSG_CPP
#include <core/LogMsg.hpp>
#include <core/Logger.hpp>

namespace attpcfe {

  LogMsg::LogMsg(Logger* logger, eLogLevel level, std::string const& file, std::size_t line) : _logger{logger}, _meta{level, file, line} {}

  LogMsg::~LogMsg()
  {
    _logger->flush(this);
  }

  LogMsg& LogMsg::operator<<(std::ostream& (*fn)(std::ostream&))
  {
    fn(_buffer);
    return *this;
  }
  
}
