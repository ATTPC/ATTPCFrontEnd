#ifndef UNITTESTABLE_INL
#define UNITTESTABLE_INL

namespace attpcfe {

  template<class T>
  UnitTestable<T>::UnitTestable()
  {
    registerSelf();
  }
  
  template<class T>
  void UnitTestable<T>::registerSelf()
  {
    static bool first{true};
    if (first)
    {
      first = false;
      UnitTestRegister::instance().registerUnitTest(TypeName<T>::value(), Test<T>());
    }
  }
}
#endif
