#define HIT_CPP
#include <hit.hpp>

#include <vector>

namespace attpcfe {

  class hit::hit_impl {

  public:
    hit_impl() {}

    std::vector<double> _position{0., 0., 0.};
    double _charge{0.};
  };

  hit::hit(std::vector<double>&& pos, double charge) : _pimpl{new hit_impl{}, [](hit_impl* ptr){ delete ptr; }}
  {
    _pimpl->_position = std::move(pos);
    _pimpl->_charge = charge;
  }
  
}
