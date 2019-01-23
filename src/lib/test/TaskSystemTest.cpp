#include <utils/TaskSystem.hpp>
#include <utils/UnitTestRegister.hpp>

using namespace attpcfe;

int main() {

  TaskSystem ts;
  UnitTestRegister::instance().runUnitTests();
  
  return 0;
}
