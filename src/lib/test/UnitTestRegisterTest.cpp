#include <utils/UnitTestRegister.hpp>
#include <utils/TaskSystem.hpp>

using namespace attpcfe;

int main() {

  TaskSystem ts;
  UnitTestRegister::instance().runUnitTests();
  
  return 0;
}
