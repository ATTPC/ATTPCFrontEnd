#ifndef TASKSYSTEM_INL
#define TASKSYSTEM_INL

namespace attpcfe {

  template<typename F, typename... Args>
  void TaskSystem::async(F&& func, Args&&... args) 
  {
    using result_t = std::invoke_result_t<F, Args...>;
    std::packaged_task<result_t()> pt{std::bind(std::forward<F>(func), std::forward<Args>(args)...)};
      
    task_t task{[pt = std::move(pt)]() mutable { pt(); }};

    // Single queue.
    //_q.push(std::move(task));
    // One queue per worker.
    //auto i = _index++;
    //_qs[i % _count].push(std::move(task));
    // Task stealing.
    auto i = _index++;
    for (unsigned int n = 0; n < _count * _K; ++n)
    {
      if (_qs[(i + n) % _count].try_push(std::move(task))) return;
    }
    _qs[i % _count].push(std::move(task));
  }

  template<typename F, typename... Args>
  auto TaskSystem::async_get(F&& func, Args&&... args)
  {
    using result_t = std::invoke_result_t<F, Args...>;
    std::packaged_task<result_t()> pt{std::bind(std::forward<F>(func), std::forward<Args>(args)...)};
    auto future = pt.get_future();
      
    task_t task{[_pt = std::move(pt)]() mutable { _pt(); }};

    auto i = _index++;
    for (unsigned int n = 0; n < _count * _K; ++n)
    {
      if (_qs[(i + n) % _count].try_push(std::move(task))) return future;
    }
    _qs[i % _count].push(std::move(task));
      
    return future;
  }

  template<typename T, typename F, typename... Args>
  auto TaskSystem::then(std::future<T>& f, F&& func, Args&&... args)   
  {
    using result_t = std::invoke_result_t<F, Args...>;
    std::packaged_task<result_t()> pt{
      [_f = std::move(f), _func = std::forward<F>(func),
       _args = std::make_tuple(std::forward<Args>(args)...)]() mutable {
	_f.wait();
	std::apply(_func, _args);
      }
    };
    auto future = pt.get_future();

    task_t task{[_pt = std::move(pt)]() mutable { _pt(); }};

    auto i = _index++;
    for (unsigned int n = 0; n < _count * _K; ++n)
    {
      if (_qs[(i + n) % _count].try_push(std::move(task))) return future;
    }
    _qs[i % _count].push(std::move(task));
      
    return future;
  }
  
}

#endif
