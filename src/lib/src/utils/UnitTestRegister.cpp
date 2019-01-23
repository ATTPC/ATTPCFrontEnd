#define UNITTESTREGISTER_CPP
#include <utils/UnitTestRegister.hpp>

#include <vector>

namespace attpcfe {

  class UnitTestRegister::UnitTestRegisterImpl {

  public:
    UnitTestRegisterImpl() {};

    std::vector<UnitTest> _unitTests;
  };

  UnitTestRegister::UnitTestRegister() : _pImpl{new UnitTestRegisterImpl{}, [](UnitTestRegisterImpl* ptr){ delete ptr; }} {}

  
  void UnitTestRegister::register_(UnitTest unitTest)
  {
    _pImpl->_unitTests.push_back(std::move(unitTest));
  }
      
  void UnitTestRegister::runUnitTests()
  {
    for (auto const& unitTest : _pImpl->_unitTests) test(unitTest);
  }
   
}
