#ifndef SIMPLENOTIFICATIONQUEUE_HPP
#define SIMPLENOTIFICATIONQUEUE_HPP
#include <deque>
#include <mutex>
#include <condition_variable>

#ifdef UNITTEST
#include <utils/UnitTestable.hpp>
#endif

namespace attpcfe {

  template<typename T>
#ifdef UNITTEST
  class SimpleNotificationQueue : public UnitTestable<SimpleNotificationQueue<T>> {

    friend struct Test<SimpleNotificationQueue<T>>;
    static void test();
#else
  class SimpleNotificationQueue {
#endif
    
    using lock_t = std::unique_lock<std::mutex>;
    
    std::deque<T> _q;
    std::mutex _mutex;

    std::condition_variable _ready;
    
  public:
    SimpleNotificationQueue() = default;
    void pop(T&);
    void push(T);
  };
}
#include <utils/SimpleNotificationQueue.inl>
#endif
