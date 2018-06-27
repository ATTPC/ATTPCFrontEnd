#define TASK_SYSTEM_CPP
#include <task_system.hpp>

namespace attpcfe {

  task_system::task_system()
  {
    for (unsigned int n = 0; n < _count; ++n)
    {
      _threads.emplace_back([&, n](){ run(n); });
    }
  }

  task_system::~task_system()
  {
    _q.done();
    for (auto& thread : _threads) thread.join();
  }

  void task_system::run(unsigned int i)
  {
    while (true)
    {
      task_t task;
      if (!_q.pop(task)) break;
      task();
    }
  }

}
