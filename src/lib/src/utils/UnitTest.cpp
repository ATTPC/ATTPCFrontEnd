#define UNITTEST_CPP
#include <utils/UnitTest.hpp>

namespace attpcfe {

  void test(UnitTest const& unitTest)
  {
    unitTest._self->test_();
  }
  
}
