// Herb Sutter's implementation
#ifndef ACTIVE_HPP
#define ACTIVE_HPP

#include <utils/SimpleQueue.hpp>

#include <functional>
#include <memory>
#include <thread>

namespace attpcfe {

  class Active {

    using Message = std::function<void()>;

    bool _done{false};
    std::unique_ptr<std::thread> _thd{nullptr};
    SimpleQueue<Message> _q;

    void run();

  public:
    Active();
    ~Active();

    Active(Active const&) = delete;
    Active& operator=(Active const&) = delete;
    Active(Active&&) = delete;
    Active& operator=(Active&&) = delete;

    void send(Message msg);
  };
}
#endif
