#ifndef SINGLETON_INL
#define SINGLETON_INL

namespace attpcfe {

  // Thread-safe since C++11 rules on initialization of static variables with local storage
  template<typename T>
  T& Singleton<T>::instance() {

    static T single;
    return single;
  }
}
#endif
