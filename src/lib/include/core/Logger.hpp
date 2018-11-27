#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <utils/Singleton.hpp>
#include <memory>

namespace attpcfe {

  class Logger : public Singleton<Logger> {

    friend class Singleton<Logger>;

    class LoggerImpl;
    std::unique_ptr<LoggerImpl, void(*)(LoggerImpl*)> _pImpl;
    
    Logger() = default;

  public:
    
  };
}
#endif;
