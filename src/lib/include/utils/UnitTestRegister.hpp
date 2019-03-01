#ifndef UNITTESTREGISTER_HPP
#define UNITTESTREGISTER_HPP
#include <utils/UnitTest.hpp>
#include <utils/Singleton.hpp>

#include <memory>

namespace attpcfe {

  class UnitTest;

  class UnitTestRegister : public Singleton<UnitTestRegister> {

    friend class Singleton<UnitTestRegister>;

    class UnitTestRegisterImpl;
    std::unique_ptr<UnitTestRegisterImpl, void(*)(UnitTestRegisterImpl*)> _pImpl;
    
    UnitTestRegister();

  public:
    void registerUnitTest(std::string const& name, UnitTest unitTest);

    template<typename T, typename F, typename... Args>
    void registerTest(T const& name, F&& func, Args&&... args);
    
    void runRegister();
  };
}
#include <utils/UnitTestRegister.inl>
#endif
