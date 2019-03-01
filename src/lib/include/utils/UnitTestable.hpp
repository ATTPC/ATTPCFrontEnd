#ifndef UNITTESTABLE_HPP
#define UNITTESTABLE_HPP
#include <utils/UnitTestRegister.hpp>

template<class>
struct TypeName;

#define REGISTER_TYPE_NAME(type, name) \
  template<> \
  struct TypeName<type> \
  { \
    static std::string const& value() \
    { \
      static std::string const typeName = #name ; \
      return typeName; \
    } \
  };

namespace attpcfe {

  template<class T>
  struct Test {

    void operator()() const { T::test(); }
  };

  template<class T>
  class UnitTestable
  {
    static void registerSelf();

  protected:
    UnitTestable();
  };
}
#include <utils/UnitTestable.inl>
#endif
