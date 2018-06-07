// Following Sean Parent's implementation in concurrency talk @ NDC 2017
// Some considerations from Mastering the C++17 STL by Arthur O'Dwyer
#ifndef TASK_SYSTEM_HPP
#define TASK_SYSTEM_HPP

#include <memory>

namespace attpcfe {

  class task_system {

    class task_system_impl;
    std::unique_ptr<task_system_impl, void(*)(task_system_impl*)> _pimpl;

  public:
    task_system();
    ~task_system();
  };
}
#endif
