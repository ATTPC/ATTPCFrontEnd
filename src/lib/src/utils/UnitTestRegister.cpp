#define UNITTESTREGISTER_CPP
#include <utils/UnitTestRegister.hpp>

#include <utils/UnitTest.hpp>

namespace attpcfe {

  void UnitTestRegister::register(UnitTest unitTest)
  {
    _unitTests.push_back(std::move(unitTest));
  }
      
  void UnitTestRegister::runUnitTests()
  {
    for (auto const& unitTest : _unitTests) unitTest();
  }
   
}
