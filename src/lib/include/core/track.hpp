#ifndef TRACK_HPP
#define TRACK_HPP

#include <memory>

namespace attpcfe {

  class track {

    class track_impl;
    std::unique_ptr<track_impl, void(*)(track_impl*)> _pimpl;

  public:
    track();
  };
}
#endif
