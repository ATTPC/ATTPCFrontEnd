#ifndef LOGMSG_HPP
#define LOGMSG_HPP

#include <utils/LogLevel.hpp>

#include <string>
#include <sstream>

namespace attpcfe {

  class Logger;
  
  class LogMsg {

  public:
    struct Meta {

      eLogLevel _level;
      std::string _file;
      std::size_t _line;
    };

  private:
    friend class Logger;
    
    LogMsg(Logger* logger, eLogLevel level, std::string const& filename, std::size_t line);
    LogMsg(LogMsg const&) = delete;
    LogMsg(LogMsg&&);

    Logger* _logger;
    Meta _meta;
    std::ostringstream _buffer;

  public:
    ~LogMsg();
    LogMsg& operator=(LogMsg const&) = delete;
    LogMsg& operator=(LogMsg&&) = delete;

    template<typename T>
    LogMsg& operator<<(T value);

    LogMsg& operator<<(std::ostream& (*fn)(std::ostream&));
  };
}
#include <utils/LogMsg.inl>
#endif
