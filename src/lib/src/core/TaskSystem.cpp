#define TASKSYSTEM_CPP
#include <core/TaskSystem.hpp>

namespace attpcfe {

  TaskSystem::TaskSystem()
  {
    for (unsigned int n = 0; n < _count; ++n)
    {
      _threads.emplace_back([&, n](){ run(n); });
    }
  }

  TaskSystem::~TaskSystem()
  {
    //_q.done();
    for (auto& q : _qs) q.done();
    for (auto& thread : _threads) thread.join();
  }

  void TaskSystem::run(unsigned int i)
  {
    while (true)
    {
      task_t task;
      //if (!_q.pop(task)) break;
      if (!_qs[i].pop(task)) break;
      task();
    }
  }

}
