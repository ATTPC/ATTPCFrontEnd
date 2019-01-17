#include <utils/Logger.hpp>
//#include <utils/TaskSystem.hpp>

#include <chrono>
#include <thread>
//#include <iostream>

using namespace std::chrono_literals;
using namespace attpcfe;

int main() {
  
  gLog << "Testing message log" << std::endl;
  gLogDebug << "Testing debug log" << std::endl;
  gLogWarning << "Testing warning log" << std::endl;
  gLogError << "Testing error log" << std::endl;
  gLogFatal << "Testing fatal log" << std::endl ;

  // Need to make sure the background thread of the active object is executed
  // before the Logger::dtor is called. Should not be a problem in production code.
  // Here add some tasks, or have main thread sleep for a bit.
  /*
  TaskSystem ts;
  for (std::size_t i = 0; i < 10; ++i)
  {
    ts.voidAsync([=](std::size_t idx){ std::cout << "> exec task " << idx << std::endl; }, i);
  }
  */
  std::this_thread::sleep_for(1s);
  
  return 0;
}
