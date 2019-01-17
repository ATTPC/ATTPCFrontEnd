// Logging framework based on tutorial from GrandMaster's Playground
#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <utils/Singleton.hpp>
#include <utils/LogMsg.hpp> // Needed for gLogLevel macro
#include <utils/LogLevel.hpp> // Needed for gLogLevel macro

#include <memory>

namespace attpcfe {

  class LogSink;
  
  class Logger : public Singleton<Logger> {

    friend class Singleton<Logger>;

    class LoggerImpl;
    std::unique_ptr<LoggerImpl, void(*)(LoggerImpl*)> _pImpl;
    
    Logger();

  public:
    void addSink(LogSink sink);
    void flush(LogMsg const* msg);

    LogMsg operator()(eLogLevel level, std::string const& filename, std::size_t line);
  };
}

// Macros to generate messages with proper logging levels
#define gLogLevel(level) (			\
        attpcfe::Logger::instance()(			\
	         attpcfe::eLogLevel::level,		\
		 __FILE__,						\
		 __LINE__						\
	))  
		     	
#define gLog        (gLogLevel(MSG))
#define gLogDebug   (gLogLevel(DBG))
#define gLogWarning (gLogLevel(WRN))
#define gLogError   (gLogLevel(ERR))
#define gLogFatal   (gLogLevel(FAT))

#endif
