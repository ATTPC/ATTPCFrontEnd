// Following Sean Parent's implementation in concurrency talk @ NDC 2017
// Some considerations from Mastering the C++17 STL by Arthur O'Dwyer
#ifndef NOTIFICATIONQUEUE_HPP
#define NOTIFICATIONQUEUE_HPP

#include <memory>
#include <future>

namespace attpcfe {

  using task_t = std::packaged_task<void()>;
  
  class NotificationQueue {

    class NotificationQueueImpl;
    std::unique_ptr<NotificationQueueImpl, void(*)(NotificationQueueImpl*)> _pImpl;

  public:
    NotificationQueue();
    
    bool pop(task_t& task);
    void push(task_t task);
    void done();
  };
}
#endif
