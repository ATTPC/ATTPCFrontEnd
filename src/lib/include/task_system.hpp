// Following Sean Parent's implementation in concurrency talk @ NDC 2017
// Some considerations from Mastering the C++17 STL by Arthur O'Dwyer
// Not using pimpl idiom because of templated async
#ifndef TASK_SYSTEM_HPP
#define TASK_SYSTEM_HPP
#include <notification_queue.hpp>

#include <thread>
#include <vector>
#include <functional>

namespace attpcfe {

  class task_system {

    const unsigned _count{std::thread::hardware_concurrency()};
    std::vector<std::thread> _threads;
    notification_queue _q;
    
  public:
    task_system();
    ~task_system();

    template <typename F, typename... Args>
    auto async(F&& func, Args&&... args) -> std::future<std::result_of_t<std::decay_t<F>(std::decay_t<Args>...)> >
    {
      using result_t = std::result_of_t<std::decay_t<F>(std::decay_t<Args>...)>;

      std::packaged_task<result_t()> pt{std::bind(std::forward<F>(func), std::forward<Args>(args)...)};
      std::future<result_t> future = pt.get_future();
      
      task_t task{[pt = std::move(pt)]() mutable { pt(); }};
      
      _q.push(std::move(task));
      
      return future;
    }

    template <typename F, typename... Args>
    void void_async(F&& func, Args&&... args) 
    {
      using result_t = std::result_of_t<std::decay_t<F>(std::decay_t<Args>...)>;

      std::packaged_task<result_t()> pt{std::bind(std::forward<F>(func), std::forward<Args>(args)...)};
      std::future<result_t> future = pt.get_future();
      
      task_t task{[pt = std::move(pt)]() mutable { pt(); }};
      
      _q.push(std::move(task));
    }
    
  private:
    void run(unsigned int i);
  };
}
#endif
