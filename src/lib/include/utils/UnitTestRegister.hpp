#ifndef UNITTESTREGISTER_HPP
#define UNITTESTREGISTER_HPP

#include <utils/Singleton.hpp>

#include <vector>

namespace attpcfe {

  class UnitTest;

  class UnitTestRegister : public Singleton<UnitTestRegister> {

    friend class Singleton<UnitTestRegister>;

    class UnitTestRegisterImpl;
    std::unique_ptr<UnitTestRegisterImpl, void(*)(UniTestRegisterImpl*)> _pImpl;
    
    UnitTestRegister() = default;

    std::vector<UnitTest> _unitTests;

  public:
    //template<typename T, typename F, typename... Args>
    void register(UnitTest unitTest);
    void runUnitTests();
  };
}
#endif
