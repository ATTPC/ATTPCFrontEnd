#define NOTIFICATION_QUEUE_CPP
#include <core/NotificationQueue.hpp>

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
    
    auto& ProtectedMembers() { return _protected; }
    auto& Condition() { return _ready; }
  };

  NotificationQueue::NotificationQueue() : _pImpl{new NotificationQueueImpl{}, [](NotificationQueueImpl* ptr){ delete ptr; }} {}

  bool NotificationQueue::Pop(task_t& task)
  {
    lock_t lock{_pImpl->ProtectedMembers()._mutex};
    while (_pImpl->ProtectedMembers()._q.empty() && !_pImpl->ProtectedMembers()._done)
      _pImpl->Condition().wait(lock);

    if (_pImpl->ProtectedMembers()._done) return false;
    
    assert(!_pImpl->ProtectedMembers()._q.empty());
    
    task = std::move(_pImpl->ProtectedMembers()._q.front());
    _pImpl->ProtectedMembers()._q.pop_front();
    return true;
  }

  void NotificationQueue::Push(task_t task)
  {
    if(lock_t lock{_pImpl->ProtectedMembers()._mutex}; true) _pImpl->ProtectedMembers()._q.push_back(std::move(task));
    _pImpl->Condition().notify_one();
  }

  void NotificationQueue::Done()
  {
    if(lock_t lock{_pImpl->ProtectedMembers()._mutex}; true) _pImpl->ProtectedMembers()._done = true;
    _pImpl->Condition().notify_all();
  }
}
