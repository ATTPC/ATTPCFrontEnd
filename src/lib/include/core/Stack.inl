#ifndef STACK_INL
#define STACK_INL

namespace attpcfe {

  template<typename T>
  void Stack<T>::reserve(std::size_t capacity)
  {
    lock_t lock{_protected._mutex};
    _protected._elements.reserve(capacity);
  }

  template<typename T>
  void Stack<T>::pop(T& element)
  {
    lock_t lock{_protected._mutex};
    element = std::move(_protected._elements.back());
    _protected._elements.pop_back();
  }

  template<typename T>
  void Stack<T>::push(T&& element)
  {
    lock_t lock{_protected._mutex};
    _protected._elements.push_back(std::move(element));
  }

  template<typename T>
  std::size_t Stack<T>::size() const
  {
    return _protected._elements.size();
  }

  template<typename T>
  T const& Stack<T>::back() const
  {
    return _protected._elements.back();
  }

  template<typename T>
  T const& Stack<T>::operator[](std::size_t idx) const
  {
    return _protected._elements[idx];
  }

  template<typename T>
  void Stack<T>::clear()
  {
    _protected._elements.clear();
    _protected._elements.shrink_to_fit();
  }

}
#endif
