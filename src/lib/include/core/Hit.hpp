#ifndef HIT_HPP
#define HIT_HPP

#include <memory>
#include <vector>

namespace attpcfe {

  class Hit {

    class HitImpl;
    std::unique_ptr<HitImpl, void(*)(HitImpl*)> _pImpl;

  public:
    Hit(std::vector<double>&& pos, double charge, int16_t padNum);

    std::vector<double> const& position() const;
    double charge() const;
    int16_t padNum() const;
  };
}
#endif
