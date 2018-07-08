#ifndef PAD_HPP
#define PAD_HPP

#include <memory>
#include <vector>

namespace attpcfe {


  class Pad {

    class PadImpl;
    std::unique_ptr<PadImpl, void(*)(PadImpl*)> _pImpl;

  public:
    Pad();

    void setRawData(std::vector<int16_t> rawData);
    std::vector<int16_t> const& rawData() const;
    std::vector<double>& data();
    int16_t cobo() const;
    int16_t asad() const;
    int16_t aget() const;
    int16_t channel() const;
    int16_t number() const;
  };
}
#endif
