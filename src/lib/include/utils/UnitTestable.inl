#ifndef UNITTESTABLE_INL
#define UNITTESTABLE_INL

namespace attpcfe {

  template<class T>
  UnitTestable<T>::UnitTestable()
  {
    register_();
  }
  
  template<class T>
  void UnitTestable<T>::register_()
  {
    static bool first{true};
    if (first)
    {
      first = false;
      UnitTestRegister::instance().register_(Test<T>());
    }
  }
}
#endif
