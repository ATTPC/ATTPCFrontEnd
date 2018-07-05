#define HIT_CPP
#include <core/Hit.hpp>

#include <vector>

namespace attpcfe {

  class Hit::HitImpl {

  public:
    HitImpl() {}

    std::vector<double> _position{0., 0., 0.};
    double _charge{0.};
  };

  Hit::Hit(std::vector<double>&& pos, double charge) : _pImpl{new HitImpl{}, [](HitImpl* ptr){ delete ptr; }}
  {
    _pImpl->_position = std::move(pos);
    _pImpl->_charge = charge;
  }
  
}
