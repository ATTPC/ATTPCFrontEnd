#ifndef UNITTESTABLE_HPP
#define UNITTESTABLE_HPP
#include <utils/UnitTestRegister.hpp>

namespace attpcfe {

  template<class T>
  struct Test {

    void operator()() const { T::test(); }
  };

  template<class T>
  class UnitTestable
  {
    static void register_();

  protected:
    UnitTestable();
  };
}
#include <utils/UnitTestable.inl>
#endif
