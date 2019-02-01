// Following Sean Parent's implementation in concurrency talk @ NDC 2017
// Some considerations from Mastering the C++17 STL by Arthur O'Dwyer
// Not using pimpl idiom because of templated async
#ifndef TASKSYSTEM_HPP
#define TASKSYSTEM_HPP
#include <utils/NotificationQueue.hpp>
#include <thread>
#include <vector>
#include <functional>

#ifdef UNITTEST
#include <utils/UnitTestable.hpp>
#endif

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
    std::vector<NotificationQueue> _qs{_count};
    std::atomic<unsigned int> _index{0};
    
  public:
    TaskSystem();
    ~TaskSystem();

    // Non future returning version of async.
    template<typename F, typename... Args>
    void async(F&& func, Args&&... args);
    
    // Future returning version of async.
    template<typename F, typename... Args>
    auto async_get(F&& func, Args&&... args);

    // Continuation.
    template<typename T, typename F, typename... Args>
    auto then(std::future<T>& f, F&& func, Args&&... args);

  private:
    void run(unsigned int i);
  };
}

#include <utils/TaskSystem.inl>
#endif
