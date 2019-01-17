#define NOTIFICATIONQUEUE_CPP
#include <utils/NotificationQueue.hpp>

#include <deque>
#include <mutex>
#include <condition_variable>
#include <cassert>

namespace attpcfe {

  using lock_t = std::unique_lock<std::mutex>;
  
  class NotificationQueue::NotificationQueueImpl {

    struct {
      std::deque<task_t> _q;
      std::mutex _mutex;
      bool _done{false};
    } _protected;
    std::condition_variable _ready;
    
  public:
    NotificationQueueImpl() {}
    
    auto& protectedMembers() { return _protected; }
    auto& condition() { return _ready; }
  };

  NotificationQueue::NotificationQueue() : _pImpl{new NotificationQueueImpl{}, [](NotificationQueueImpl* ptr){ delete ptr; }} {}

  bool NotificationQueue::pop(task_t& task)
  {
    lock_t lock{_pImpl->protectedMembers()._mutex};
    while (_pImpl->protectedMembers()._q.empty() && !_pImpl->protectedMembers()._done) // Protects from spurious wakes
      _pImpl->condition().wait(lock);

    if (_pImpl->protectedMembers()._done) return false;
    
    //assert(!_pImpl->protectedMembers()._q.empty());
    
    task = std::move(_pImpl->protectedMembers()._q.front());
    _pImpl->protectedMembers()._q.pop_front();
    return true;
  }

  void NotificationQueue::push(task_t task)
  {
    if(lock_t lock{_pImpl->protectedMembers()._mutex}; true) _pImpl->protectedMembers()._q.push_back(std::move(task));
    _pImpl->condition().notify_one();
  }

  // For task stealing.
  bool NotificationQueue::try_pop(task_t& task)
  {
    lock_t lock{_pImpl->protectedMembers()._mutex, std::try_to_lock};
    if (!lock || _pImpl->protectedMembers()._q.empty()) return false;

    task = std::move(_pImpl->protectedMembers()._q.front());
    _pImpl->protectedMembers()._q.pop_front();
    return true;
  }

  bool NotificationQueue::try_push(task_t task)
  {
    if (lock_t lock{_pImpl->protectedMembers()._mutex, std::try_to_lock}; !lock) return false;
    _pImpl->protectedMembers()._q.push_back(std::move(task));
    _pImpl->condition().notify_one();
    return true;
  }

  void NotificationQueue::done()
  {
    if(lock_t lock{_pImpl->protectedMembers()._mutex}; true) _pImpl->protectedMembers()._done = true;
    _pImpl->condition().notify_all();
  }
}
