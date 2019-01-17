#ifndef SIMPLENOTIFICATIONQUEUE_INL
#define SIMPLENOTIFICATIONQUEUE_INL

namespace attpcfe {
  
  template <typename T>
  void SimpleNotificationQueue<T>::pop(T& task) {

    lock_t lock{_mutex};
    while (_q.empty()) 
      _ready.wait(lock);

    task = std::move(_q.front());
    _q.pop_front();
  }
  
  template <typename T>
  void SimpleNotificationQueue<T>::push(T task) {

    if(lock_t lock{_mutex}; true) _q.push_back(std::move(task));
    _ready.notify_one();
  }
}
#endif
