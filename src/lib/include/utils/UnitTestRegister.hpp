#ifndef UNITTESTREGISTER_HPP
#define UNITTESTREGISTER_HPP
#include <utils/UnitTest.hpp>
#include <utils/Singleton.hpp>

#include <memory>

#include <future>

namespace attpcfe {

  class UnitTest;

  class UnitTestRegister : public Singleton<UnitTestRegister> {

    friend class Singleton<UnitTestRegister>;

    class UnitTestRegisterImpl;
    std::unique_ptr<UnitTestRegisterImpl, void(*)(UnitTestRegisterImpl*)> _pImpl;
    
    UnitTestRegister();

  public:
    void register_(UnitTest unitTest);

    template<typename F, typename... Args>
    void register_func(F&& func, Args&&... args);
    //template <typename Base, typename F, typename I, typename... Args>
    //void reg_(F Base::*f, I&& instance, Args&&... args);
    
    void runUnitTests();
  };
}
#include <utils/UnitTestRegister.inl>
#endif
