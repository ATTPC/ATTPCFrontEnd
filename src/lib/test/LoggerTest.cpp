#include <core/Logger.hpp>

using namespace attpcfe;

int main() {

  gLog << "Testing message log" << std::endl;
  gLogDebug << "Testing debug log";
  gLogWarning << "Testing warning log";
  gLogError << "Testing error log";
  gLogFatal << "Testing fatal log";
  
  return 0;
}
