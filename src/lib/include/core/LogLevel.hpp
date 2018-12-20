#ifndef LOGLEVEL_HPP
#define LOGLEVEL_HPP

#include <ostream>

namespace attpcfe {

  enum class eLogLevel {
    MSG, // Simple message
    DBG, // Debug message
    WRN, // Warning message
    ERR, // Error message
    FAT  // Fatal error message
  };
}

std::ostream& operator<<(std::ostream& os, attpcfe::eLogLevel const& level);

#endif
