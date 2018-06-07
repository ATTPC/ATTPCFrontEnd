#define TASK_SYSTEM_CPP
#include <task_system.hpp>

#include <thread>
#include <vector>
#include <notification_queue.hpp>

namespace attpcfe {

  class task_system::task_system_impl {

    const unsigned _count{std::thread::hardware_concurrency()};
    std::vector<std::thread> _threads;
    notification_queue _q;
    
  public:
    task_system_impl() {}

    auto count() { return _count; }
    auto& threads() { return _threads; }
    auto& queue() { return _q; }

    void run(unsigned int i)
    {
      while (true)
      {
	task_t task;
	_q.pop(task);
	//if (_q.pop(task)) task();
	//else break;
	task();
      }
    }
  };

  task_system::task_system() : _pimpl{new task_system_impl, [](task_system_impl* ptr){ delete ptr; }}
  {
    for (unsigned int n = 0; n < _pimpl->count(); ++n)
    {
      _pimpl->threads().emplace_back([&, n](){ _pimpl->run(n); });
    }
  }

  task_system::~task_system()
  {
    _pimpl->queue().done();
    for (auto& thread : _pimpl->threads()) thread.join();
  }

}
