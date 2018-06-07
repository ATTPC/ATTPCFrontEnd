#ifndef NOTIFICATION_QUEUE_HPP
#define NOTIFICATION_QUEUE_HPP

#include <memory>
#include <future>

namespace attpcfe {

  using task_t = std::packaged_task<void()>;
  
  class notification_queue {

    class notification_queue_impl;
    std::unique_ptr<notification_queue_impl, void(*)(notification_queue_impl*)> _pimpl;

  public:
    notification_queue();
    
    bool pop(task_t& task);
    void push(task_t task);
    void done();
  };
}
#endif
