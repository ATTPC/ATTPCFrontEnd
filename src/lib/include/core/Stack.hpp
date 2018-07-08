#ifndef STACK_HPP
#define STACK_HPP

#include <vector>
#include <mutex>

namespace attpcfe {

  using lock_t = std::unique_lock<std::mutex>;

  template<typename T>
  class Stack {

    struct {
      std::vector<T> _elements;
      std::mutex _mutex;
    } _protected;

  public:
    Stack() {};

    void reserve(std::size_t capacity)
    {
      lock_t lock{_protected._mutex};
      _protected._elements.reserve(capacity);
    }

    void pop(T& element)
    {
      lock_t lock{_protected._mutex};
      element = std::move(_protected._elements.back());
      _protected._elements.pop_back();
    }

    void push(T&& element)
    {
      lock_t lock{_protected._mutex};
      _protected._elements.push_back(std::move(element));
    }

    std::size_t size()
    {
      lock_t lock{_protected._mutex};
      return _protected._elements.size();
    }
  };
}
#endif
