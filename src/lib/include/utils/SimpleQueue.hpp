#ifndef SIMPLEQUEUE_HPP
#define SIMPLEQUEUE_HPP

#include <deque>
#include <mutex>

namespace attpcfe {

  template <typename T>
  class SimpleQueue {

    using lock_t = std::scoped_lock<std::mutex>;
    
    std::deque<T> _q;
    std::mutex _mutex;
    
  public:
    SimpleQueue() = default;
    bool _empty();
    void pop(T&);
    void push(T);
  };
}
#include <utils/SimpleQueue.inl>
#endif
