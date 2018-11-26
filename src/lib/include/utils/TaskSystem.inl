#ifndef TASKSYSTEM_INL
#define TASKSYSTEM_INL

namespace attpcfe {

  template<typename F, typename... Args>
  void TaskSystem::voidAsync(F&& func, Args&&... args) 
  {
    using result_t = std::result_of_t<std::decay_t<F>(std::decay_t<Args>...)>;

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

  /*
  template<typename F, typename... Args>
  auto TaskSystem::async(F&& func, Args&&... args)
  -> std::future<std::result_of_t<std::decay_t<F>(std::decay_t<Args>...)> >
  //std::future<std::result_of_t<std::decay_t<F>(std::decay_t<Args>...)> > TaskSystem::async(F&& func, Args&&... args)
  {
    using result_t = std::result_of_t<std::decay_t<F>(std::decay_t<Args>...)>;

    std::packaged_task<result_t()> pt{std::bind(std::forward<F>(func), std::forward<Args>(args)...)};
    std::future<result_t> future = pt.get_future();
      
    task_t task{[pt = std::move(pt)]() mutable { pt(); }};

    auto i = _index++;
    for (unsigned int n = 0; n < _count * _K; ++n)
    {
      if (_qs[(i + n) % _count].try_push(std::move(task))) return future;
    }
    _qs[i % _count].push(std::move(task));
      
    return future;
  }
  */
  /*
  template<typename MemberType, typename Base, typename... Args>
  auto TaskSystem::async(MemberType Base::* func, Base&& base, Args&&... args)
    -> std::future<std::result_of_t<std::decay_t<MemberType>(std::decay_t<Args>...)> >
  {
    using result_t = std::result_of_t<std::decay_t<MemberType>(std::decay_t<Args>...)>;

    std::packaged_task<result_t()> pt{std::bind(std::forward<Base>(base).*func, std::forward<Args>(args)...)};
    std::future<result_t> future = pt.get_future();
      
    task_t task{[pt = std::move(pt)]() mutable { pt(); }};

    auto i = _index++;
    for (unsigned int n = 0; n < _count * _K; ++n)
    {
      if (_qs[(i + n) % _count].try_push(std::move(task))) return future;
    }
    _qs[i % _count].push(std::move(task));
      
    return future;
  }
  */
  
}

#endif
