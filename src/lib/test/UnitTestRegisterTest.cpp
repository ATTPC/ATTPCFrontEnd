#include <utils/UnitTestRegister.hpp>
#include <utils/SimpleNotificationQueue.hpp>
#include <utils/TaskSystem.hpp>
#include <utils/Logger.hpp>

using namespace attpcfe;

int main() {

  SimpleNotificationQueue<std::function<void()>> q;
  TaskSystem ts;
  Logger::instance();
  
  UnitTestRegister::instance().runUnitTests();
  
  return 0;
}
