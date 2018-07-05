#define TASKSYSTEM_CPP
#include <core/TaskSystem.hpp>

namespace attpcfe {

  TaskSystem::TaskSystem()
  {
    for (unsigned int n = 0; n < _count; ++n)
    {
      _threads.emplace_back([&, n](){ Run(n); });
    }
  }

  TaskSystem::~TaskSystem()
  {
    _q.Done();
    for (auto& thread : _threads) thread.join();
  }

  void TaskSystem::Run(unsigned int i)
  {
    while (true)
    {
      task_t task;
      if (!_q.Pop(task)) break;
      task();
    }
  }

}
