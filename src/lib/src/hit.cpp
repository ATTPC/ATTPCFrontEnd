#define HIT_CPP
#include <hit.hpp>

#include <vector>

namespace attpcfe {

  class hit::hit_impl {

  public:
    hit_impl() {}

    double _charge{0.};
    std::vector<double> _position{0., 0., 0.};
  };

  hit::hit() : _pimpl{new hit_impl{}, [](hit_impl* ptr){ delete ptr; }} {}
  
}
