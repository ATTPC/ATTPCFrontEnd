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

    void Reserve(std::size_t capacity)
    {
      lock_t lock{_protected._mutex};
      _protected._elements.reserve(capacity);
    }

    void Pop(T& element)
    {
      lock_t lock{_protected._mutex};
      element = std::move(_protected._elements.back());
      _protected._elements.pop_back();
    }

    void Push(T&& element)
    {
      lock_t lock{_protected._mutex};
      _protected._elements.push_back(std::move(element));
    }

    std::size_t Size()
    {
      lock_t lock{_protected._mutex};
      return _protected._elements.size();
    }
    
    //T const& operator[](std::size_t pos)
    //{
    //  return _protected._elements[pos];
    //}
  };
}
#endif
