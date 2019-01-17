#define ACTIVE_CPP
#include <utils/Active.hpp>

namespace attpcfe {

  Active::Active() {

    _thd = std::unique_ptr<std::thread>(new std::thread([=]{ this->run(); }));
  }

  Active::~Active() {

    send([&](){ _done = true; });
    _thd->join();
  }

  void Active::run() {

    while (!_done) {

      Message msg;
      _q.pop(msg);
      msg();
    }
  }

  void Active::send(Message msg) {

    _q.push(msg);
  }
}
