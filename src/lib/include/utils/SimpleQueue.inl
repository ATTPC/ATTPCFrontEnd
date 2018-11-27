#ifndef SIMPLEQUEUE_INL
#define SIMPLEQUEUE_INL

namespace attpcfe {

  template <typename T>
  void SimpleQueue<T>::pop(T& task) {

    lock_t lock{_mutex};
    task = std::move(_q.front());
    _q.pop_front();
  }
  
  template <typename T>
  void SimpleQueue<T>::push(T task) {

    lock_t lock{_mutex};
    _q.push_back(std::move(task));
  }
}
#endif
