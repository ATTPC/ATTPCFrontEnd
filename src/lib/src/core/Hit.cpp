#define HIT_CPP
#include <core/Hit.hpp>

#include <vector>

namespace attpcfe {

  class Hit::HitImpl {

  public:
    HitImpl() {}

    std::vector<double> _position{0., 0., 0.};
    double _charge{0.};
    std::size_t _padNum{0};
  };

  Hit::Hit(std::vector<double>&& pos, double charge, std::size_t padNum) : _pImpl{new HitImpl{}, [](HitImpl* ptr){ delete ptr; }}
  {
    _pImpl->_position = std::move(pos);
    _pImpl->_charge = charge;
    _pImpl->_padNum = padNum;
  }
  
}
