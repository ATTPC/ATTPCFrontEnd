#define LOGLEVEL_CPP
#include <utils/LogLevel.hpp>

std::ostream& operator<<(std::ostream& os, attpcfe::eLogLevel const& level)
{
  using attpcfe::eLogLevel;
  
  switch(level) {
  case eLogLevel::MSG: os << "> msg "; break;
  case eLogLevel::DBG: os << "> [dbg] "; break;
  case eLogLevel::WRN: os << "> *wrn* "; break;
  case eLogLevel::ERR: os << "> < ERROR > "; break;
  case eLogLevel::FAT: os << "> <## FATAL ##> "; break;
  default: os << "> unknown level";
  }
  
  return os;
}
