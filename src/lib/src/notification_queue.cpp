#define NOTIFICATION_QUEUE_CPP
#include <notification_queue.hpp>

#include <deque>
#include <mutex>
#include <condition_variable>

namespace attpcfe {

  using lock_t = std::unique_lock<std::mutex>;
  
  class notification_queue::notification_queue_impl {

    struct {
      std::deque<task_t> _q;
      std::mutex _mutex;
      bool _done{false};
    } _protected;
    std::condition_variable _ready;
    
  public:
    notification_queue_impl() {}
    
    auto& protected_members() { return _protected; }
    auto& condition() { return _ready; }
  };

  notification_queue::notification_queue() : _pimpl{new notification_queue_impl{}, [](notification_queue_impl* ptr){ delete ptr; }} {}

  bool notification_queue::pop(task_t& task)
  {
    lock_t lock{_pimpl->protected_members()._mutex};
    while (_pimpl->protected_members()._q.empty() && !_pimpl->protected_members()._done)
      _pimpl->condition().wait(lock);
    if (_pimpl->protected_members()._q.empty()) return false;
    task = std::move(_pimpl->protected_members()._q.front());
    _pimpl->protected_members()._q.pop_front();
    return true;
  }

  void notification_queue::push(task_t task)
  {
    if(lock_t lock{_pimpl->protected_members()._mutex}; true) _pimpl->protected_members()._q.push_back(std::move(task));
    _pimpl->condition().notify_one();
  }

  void notification_queue::done()
  {
    if(lock_t lock{_pimpl->protected_members()._mutex}; true) _pimpl->protected_members()._done = true;
    _pimpl->condition().notify_all();
  }
}
