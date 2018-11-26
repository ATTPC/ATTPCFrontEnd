#ifndef SINGLETON_INL
#define SINGLETON_INL

namespace attpcfe {

  template<typename T>
  T& Singleton<T>::instance() {

    static T single;
    return single;
  }
}
#endif;
