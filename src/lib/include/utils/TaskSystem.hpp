// Following Sean Parent's implementation in concurrency talk @ NDC 2017
// Some considerations from Mastering the C++17 STL by Arthur O'Dwyer
// Not using pimpl idiom because of templated async
#ifndef TASKSYSTEM_HPP
#define TASKSYSTEM_HPP
#include <utils/UnitTestable.hpp>
#include <utils/NotificationQueue.hpp>

#include <thread>
#include <vector>
#include <functional>

#define UNITTEST 1;

namespace attpcfe {

  #ifdef UNITTEST
  class TaskSystem : public UnitTestable<TaskSystem> {

    friend struct Test<TaskSystem>;
    static void test();
  #else
  class TaskSystem {
  #endif

    const unsigned int _count{std::thread::hardware_concurrency()};
    const unsigned int _K{3};
    std::vector<std::thread> _threads;
    //NotificationQueue _q;
    std::vector<NotificationQueue> _qs{_count};
    std::atomic<unsigned int> _index{0};
    
  public:
    TaskSystem();
    ~TaskSystem();

    // Non returning version of async.
    template<typename F, typename... Args>
    void voidAsync(F&& func, Args&&... args);
    
    // Future returning version of async.
    template<typename F, typename... Args>
    auto async(F&& func, Args&&... args)
    //-> std::future<std::result_of_t<std::decay_t<F>(std::decay_t<Args>...)> > 
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
 
    // Future returning version of async for member functions.
    template<typename MemberType, typename Base, typename... Args>
    auto async(MemberType Base::* func, Base&& base, Args&&... args)
    //-> std::future<std::result_of_t<std::decay_t<MemberType>(std::decay_t<Args>...)> >
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

    // Continuation.
    template<typename T, typename F, typename... Args>
    std::future<T> then(std::future<T>& f, F&& func, Args&&... args) 
    {
      std::packaged_task<void()> pt{
	[_f = std::move(f), _func = std::forward<F>(func),
	 _args = std::make_tuple(std::forward<Args>(args)...)]() mutable {
	  _f.wait();
	  std::apply(_func, _args);
	}
      };

      auto future = pt.get_future();

      task_t task{[pt = std::move(pt)]() mutable { pt(); }};

      auto i = _index++;
      for (unsigned int n = 0; n < _count * _K; ++n)
      {
	if (_qs[(i + n) % _count].try_push(std::move(task))) return future;
      }
      _qs[i % _count].push(std::move(task));
      
      return future;
    }

    // Version of continuation for member functions.
    template<typename T, typename MemberType, typename Base, typename... Args>
    std::future<T> then(std::future<T>& f, MemberType Base::* func, Base&& base, Args&&... args) 
    {
      std::packaged_task<void()> pt{
	[_f = std::move(f), _func = std::forward<Base>(base).*func,
	 _args = std::make_tuple(std::forward<Args>(args)...)]() mutable {
	  _f.wait();
	  std::apply(_func, _args);
	}
      };

      auto future = pt.get_future();

      task_t task{[pt = std::move(pt)]() mutable { pt(); }};

      auto i = _index++;
      for (unsigned int n = 0; n < _count * _K; ++n)
      {
	if (_qs[(i + n) % _count].try_push(std::move(task))) return future;
      }
      _qs[i % _count].push(std::move(task));

      return future;
    }
    
  private:
    void run(unsigned int i);
  };
}

#include <utils/TaskSystem.inl>
#endif
