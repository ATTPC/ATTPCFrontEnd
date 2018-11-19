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
    Stack() = default;

    void reserve(std::size_t capacity);
    void pop(T& element);
    void push(T&& element);
 
    // Following methods are not thread safe 
    std::size_t size() const;
    T const& back() const;
    T const& operator[](std::size_t idx) const;
    void clear();
  };
}

#include <core/Stack.inl>
#endif
