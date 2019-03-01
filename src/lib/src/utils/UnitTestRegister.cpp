#define UNITTESTREGISTER_CPP
#include <utils/UnitTestRegister.hpp>
#include <vector>
#include <iostream>

namespace attpcfe {

  class UnitTestRegister::UnitTestRegisterImpl {

  public:
    UnitTestRegisterImpl() {};

    std::vector<std::pair<std::string, UnitTest>> _unitTests;
  };

  UnitTestRegister::UnitTestRegister() : _pImpl{new UnitTestRegisterImpl{}, [](UnitTestRegisterImpl* ptr){ delete ptr; }} {}

  void UnitTestRegister::registerUnitTest(std::string const& name, UnitTest unitTest)
  {
    _pImpl->_unitTests.emplace_back(name, std::move(unitTest));
  }
  
  void UnitTestRegister::runRegister()
  {
    for (auto const& [name, unitTest] : _pImpl->_unitTests)
    {
      std::cout << "> running unit test on: " << name << '\n';
      test(unitTest);
    }
  }
   
}
