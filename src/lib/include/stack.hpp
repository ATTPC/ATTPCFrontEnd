#ifndef STACK_HPP
#define STACK_HPP

#include <vector>
#include <mutex>

namespace attpcfe {

  using lock_t = std::unique_lock<std::mutex>;

  template<typename T>
  class stack {

    struct {
      std::vector<T> _elements;
      std::mutex _mutex;
    } _protected;

  public:
    stack() {};

    auto& protected_members() { return _protected; }

    void pop(T& element)
    {
      lock_t lock{_protected._mutex};
      element = std::move(_protected._elements.back());
      _protected._elements.pop_back();
    }

    void push(T element)
    {
      lock_t lock{_protected._mutex};
      _protected._elements.push_back(std::move(element));
    }
  };
}
#endif
