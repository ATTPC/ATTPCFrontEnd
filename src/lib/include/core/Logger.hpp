#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <utils/Singleton.hpp>

namespace attpfe {

  class Logger : public Singleton<Logger> {

    friend class Singleton<Logger>;
    Logger() = default;

  public:
    
  };
}
#endif;
