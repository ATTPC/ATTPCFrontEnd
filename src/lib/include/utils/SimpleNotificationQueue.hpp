#ifndef SIMPLENOTIFICATIONQUEUE_HPP
#define SIMPLENOTIFICATIONQUEUE_HPP

#include <deque>
#include <mutex>
#include <condition_variable>

namespace attpcfe {

  template <typename T>
  class SimpleNotificationQueue {

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
