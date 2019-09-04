#include <utils/Logger.hpp>
#include <utils/UnitTestRegister.hpp>
#include <chrono>
#include <thread>

using namespace std::chrono_literals;
using namespace attpcfe;

int main() {

  Logger::instance();
  UnitTestRegister::instance().runRegister();

  // Need to make sure the background thread of the active object is executed
  // before the Logger::dtor is called. Should not be a problem in production code.
  std::this_thread::sleep_for(1s);
  
  return 0;
}
