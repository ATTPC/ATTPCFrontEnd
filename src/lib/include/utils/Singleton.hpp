#ifndef SINGLETON_HPP
#define SINGLETON_HPP

namespace attpcfe {

  template<typename T>
  class Singleton {

  protected:
    Singleton() = default;

  public:
    Singleton(Singleton const&) = delete;
    Singleton& operator=(Singleton const&) = delete;

    static T& instance();
  };
}

#include <utils/Singleton.inl>
#endif
