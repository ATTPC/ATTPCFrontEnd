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
      // Single queue
      //if (!_q.pop(task)) break;
      // One queue per worker
      //if (!_qs[i].pop(task)) break;
      // Task stealing
      for (unsigned int n = 0; n < _count; ++n)
      {
	if (_qs[(i + n) % _count].try_pop(task)) break;
      }

      if (!task.valid() && !_qs[i].pop(task)) break;
      
      task();
    }
  }

}
